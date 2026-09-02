cmake_minimum_required(VERSION 3.15)

project(Rotating_Ascii CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_subdirectory(src)

add_executable(Rotating_Ascii main.cpp)

target_compile_options(Rotating_Ascii PRIVATE
    -Wall
    -Wextra
    -ggdb
    -O4
)

