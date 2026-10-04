cmake_minimum_required(VERSION 3.15)

set(
    Transformation_Src
    src/Angle.cpp
    src/Geometry.cpp
    src/Projection.cpp
    src/Rotation.cpp
    src/RotationMatrice.cpp
    )

add_library(
    Transformation
    STATIC
    ${Transformation_Src}
    )

target_link_libraries(
    Transformation
    PRIVATE
    Util
    )

target_include_directories(
    Transformation
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )