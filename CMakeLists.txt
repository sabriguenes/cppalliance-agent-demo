cmake_minimum_required(VERSION 3.16)
project(cppalliance-demo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable SSE2 for SIMD intrinsics on both Clang and GCC
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-msse2)
endif()

add_executable(demo
    src/example.cpp
    src/simd_utils.cpp
)
