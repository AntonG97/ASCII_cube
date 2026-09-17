cmake_minimum_required(VERSION 3.15)

project(Rotating_Ascii CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

option(ASCII_DEBUG_INFO "Compile all targets with debug symbols" OFF)

if(ASCII_DEBUG_INFO)
    add_compile_options(
        "$<$<COMPILE_LANGUAGE:CXX>:-g>"
        "$<$<COMPILE_LANGUAGE:CXX>:-O0>"
    )
endif()

add_subdirectory(src)
