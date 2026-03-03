cmake_minimum_required(VERSION 3.16)
project(cppalliance-demo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Note: no -stdlib=libc++ set here intentionally.
# When building with Clang on Linux using GCC headers,
# this causes "definition of builtin function" errors for SIMD intrinsics.

add_executable(demo
    src/example.cpp
    src/simd_utils.cpp
)
