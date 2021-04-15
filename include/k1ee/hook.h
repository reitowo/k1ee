#pragma once
#include <functional>
#include <map>

#pragma comment(lib, "kernel32.lib")

namespace k1ee
{
	enum hook_mode
	{
		hook_mode_normal,
		hook_mode_replace,
	};

	enum hook_return
	{
		hook_ret_normal,
		hook_ret_before,
		hook_ret_after
	};

	extern "C" __declspec(dllimport) int VirtualProtect(void* lpAddress, uint64_t dwSize,
	                                                    unsigned long flNewProtect, unsigned long* lpflOldProtect);

	static constexpr uint32_t page_execute_readwrite = 0x40;

	inline static std::map<int, std::shared_ptr<void>> ctx_map;

	template <typename FuncType>
	class hook_ctx;

	template <typename Ret, typename... Args>
	class hook_ctx<Ret(Args ...)>
	{
		using context_type = hook_ctx<Ret(Args ...)>;
	public:
		hook_mode mode = hook_mode_normal;
		hook_return ret_with = hook_ret_normal;

		uint8_t old_bytes[5] = {0};
		uint8_t new_bytes[5] = {0};

		Ret (*hookee)(Args ...) = nullptr;
		Ret (*wrapper)(Args ...) = nullptr;
		Ret (*hooker_before)(context_type*, Args ...) = nullptr;
		Ret (*hooker_after)(context_type*, Args ...) = nullptr;

		hook_ctx()
		{
			new_bytes[0] = 0xE9;
		}

		void init()
		{
			unsigned long t;

			VirtualProtect(reinterpret_cast<void*>(hookee), 5, page_execute_readwrite, &t);
			memcpy(old_bytes, reinterpret_cast<void*>(hookee), 5);
			*reinterpret_cast<uint32_t*>(&new_bytes[1]) =
				static_cast<uint32_t>(reinterpret_cast<uint64_t>(wrapper) - reinterpret_cast<uint64_t>(hookee) - 5);
			memcpy(reinterpret_cast<void*>(hookee), new_bytes, 5);
		}

		void enter() const
		{
			memcpy(reinterpret_cast<void*>(hookee), old_bytes, 5);
		}

		void leave() const
		{
			memcpy(reinterpret_cast<void*>(hookee), new_bytes, 5);
		}
	};

	template <int Id, typename FuncType>
	class hook_wrapper;

	template <int Id, typename Ret, typename... Args>
	class hook_wrapper<Id, Ret(Args ...)>
	{
		using target_func_type = Ret(Args ...);
		using context_type = hook_ctx<target_func_type>;
		using hook_func_type = Ret(context_type*, Args ...);

	public:
		static target_func_type* generate()
		{
			return [](Args ... args) -> Ret
			{
				auto ctx = std::static_pointer_cast<context_type>(ctx_map[Id]);

				Ret ret_val;

				ctx->enter();

				switch (ctx->mode)
				{
				default:
				case hook_mode_normal:
					{
						Ret before;
						Ret origin;
						Ret after;

						if (ctx->hooker_before != nullptr)
							before = ctx->hooker_before(ctx.get(), args...);
						origin = ctx->hookee(args...);
						if (ctx->hooker_after != nullptr)
							after = ctx->hooker_after(ctx.get(), args...);

						switch (ctx->ret_with)
						{
						default:
						case hook_ret_normal:
							ret_val = origin;
							break;
						case hook_ret_before:
							ret_val = before;
							break;
						case hook_ret_after:
							ret_val = after;
							break;
						}
						break;
					}
				case hook_mode_replace:
					{
						if (ctx->hooker_before != nullptr)
							ret_val = ctx->hooker_before(ctx.get(), args...);
						break;
					}
				}

				ctx->leave();

				return ret_val;
			};
		}
	};

	template <int Id, typename... Args>
	class hook_wrapper<Id, void(Args ...)>
	{
		using target_func_type = void(Args ...);
		using context_type = hook_ctx<target_func_type>;
		using hook_func_type = void(context_type*, Args ...);

	public:
		static target_func_type* generate()
		{
			return [](Args ... args)
			{
				auto ctx = std::static_pointer_cast<context_type>(ctx_map[Id]);

				ctx->enter();

				switch (ctx->mode)
				{
				default:
				case hook_mode_normal:
					{
						if (ctx->hooker_before != nullptr)
							ctx->hooker_before(ctx.get(), args...);
						ctx->hookee(args...);
						if (ctx->hooker_after != nullptr)
							ctx->hooker_after(ctx.get(), args...);
						break;
					}
				case hook_mode_replace:
					{
						if (ctx->hooker_before != nullptr)
							ctx->hooker_before(ctx.get(), args...);
						break;
					}
				}

				ctx->leave();
			};
		}
	};

	template <int Id, typename Func>
	class hook;

	template <int Id, typename Ret, typename ...Args>
	class hook<Id, Ret(Args ...)>
	{
	public:
		using target_func_type = Ret(Args ...);
		using context_type = hook_ctx<target_func_type>;
		using hook_func_type = Ret(context_type*, Args ...);

		static void hook_replace(const uintptr_t base, const uintptr_t offset,
		                         hook_func_type* replace)
		{
			hook_replace(reinterpret_cast<Ret(*)(Args ...)>(base + offset), replace);
		}

		static void hook_replace(Ret (*address)(Args ...),
		                         hook_func_type* replace)
		{
			hook_func(address, replace, nullptr, hook_mode_replace, hook_ret_normal);
		}

		static void hook_normal(const uintptr_t base, const uintptr_t offset,
		                        hook_func_type* before,
		                        hook_func_type* after)
		{
			hook_func(reinterpret_cast<Ret(*)(Args ...)>(base + offset), before, after, hook_mode_normal,
			          hook_ret_normal);
		}

		static void hook_normal_before(const uintptr_t base, const uintptr_t offset,
		                               hook_func_type* before)
		{
			hook_func(reinterpret_cast<Ret(*)(Args ...)>(base + offset), before, nullptr, hook_mode_normal,
			          hook_ret_normal);
		}

		static void hook_normal_before(Ret (*address)(Args ...),
		                               hook_func_type* before)
		{
			hook_func(address, before, nullptr, hook_mode_normal,
			          hook_ret_normal);
		}

		static void hook_normal_after(const uintptr_t base, const uintptr_t offset,
		                              hook_func_type* after)
		{
			hook_func(reinterpret_cast<Ret(*)(Args ...)>(base + offset), nullptr, after, hook_mode_normal,
			          hook_ret_normal);
		}

		static void hook_normal_after(Ret (*address)(Args ...),
		                              hook_func_type* after)
		{
			hook_func(address, nullptr, after, hook_mode_normal,
			          hook_ret_normal);
		}

		static void hook_func(const uintptr_t base, const uintptr_t offset,
		                      hook_func_type* before,
		                      hook_func_type* after,
		                      const hook_mode mode, const hook_return ret)
		{
			hook_func(reinterpret_cast<Ret(*)(Args ...)>(base + offset), before, after, mode, ret);
		}

		static void hook_func(Ret (*hookee)(Args ...),
		                      hook_func_type* before,
		                      hook_func_type* after,
		                      hook_mode mode, hook_return ret)
		{
			auto ctx = std::make_shared<context_type>();
			ctx_map[Id] = std::static_pointer_cast<void>(ctx);
			ctx->mode = mode;
			ctx->ret_with = ret;
			ctx->hookee = static_cast<Ret(*)(Args ...)>(hookee);
			ctx->hooker_before = before;
			ctx->hooker_after = after;
			ctx->wrapper = hook_wrapper<Id, target_func_type>::generate();
			ctx->init();
		}
	};
}
