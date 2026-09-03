cmake_minimum_required(VERSION 3.15)

set(Util_Sources
    src/Face.cpp
    src/Vec3.cpp
    )

add_library(Util 
    STATIC 
    ${Util_Sources}
    )

target_include_directories(
    Util 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
