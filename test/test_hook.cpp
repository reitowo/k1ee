#include "k1ee/hook.h"

#include <cassert> 

int func_1()
{
	return 100;
}

int func_2(int arg)
{
	return arg;
}

int func_3(int arg)
{
	return arg * arg;
}

int main()
{  
	k1ee::hook<1, int()>::hook_replace(&func_1, [](auto ctx) -> int
	{
		return 99;
	}); 

	assert(func_1() == 99);

	k1ee::hook<2, int(int)>::hook_normal_before(&func_2, [](auto ctx, int arg) -> int
	{
		assert(arg == 99);
		return 0;
	});

	func_2(99);
	
	k1ee::hook<3, int(int)>::hook_replace(&func_3, [](auto ctx, int arg) -> int
	{
		return ctx->hookee(arg + 1);
	});

	assert(func_3(99) == 10000);
}
