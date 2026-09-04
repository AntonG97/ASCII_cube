cmake_minimum_required(VERSION 3.15)

set(Shape_Src
    src/Cube.cpp
    src/Factory.cpp
    src/Octahedron.cpp
    src/Pyramid.cpp
    )

add_library(Shape
    STATIC
    ${Shape_Src}
    )

target_link_libraries(Shape
    PUBLIC
    Util
    )

target_include_directories(
    Shape
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
