cmake_minimum_required(VERSION 3.16)
project(cppalliance-demo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# When building with Clang, prevent GCC's intrinsic headers (xmmintrin.h, etc.)
# from shadowing Clang's builtin headers. GCC defines SSE intrinsics like
# _mm_getcsr/_mm_setcsr as inline functions, but Clang treats them as compiler
# builtins, causing "definition of builtin function" errors.
# -nostdlibinc removes standard library include paths while preserving Clang's
# own builtin intrinsic headers.
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-nostdlibinc)
endif()

add_executable(demo
    src/example.cpp
    src/simd_utils.cpp
    src/json_value.cpp
)