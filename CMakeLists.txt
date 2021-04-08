# CMakeList.txt: k1ee 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.15)

project (k1ee VERSION 1.0 LANGUAGES CXX)

# allow CMake to organize your files by folders
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib) 
# set(K1EE_LIBRARIES k1ee CACHE INTERNAL "")
 
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

option(BUILD_K1EE_TESTS "Build Tests" ON)

include(GNUInstallDirs)

add_subdirectory(src)
add_subdirectory(include)

if(BUILD_K1EE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()