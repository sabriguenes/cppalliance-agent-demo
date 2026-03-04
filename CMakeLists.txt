cmake_minimum_required(VERSION 3.16)
project(cppalliance-demo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(demo
    src/example.cpp
    src/simd_utils.cpp
    src/json_value.cpp
)