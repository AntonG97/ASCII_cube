cmake_minimum_required(VERSION 3.15)

add_executable(Rotating_Ascii main.cpp)

add_subdirectory(Util)
add_subdirectory(Shape)

target_link_libraries(Rotating_Ascii
    Util
    Shape
    )

target_compile_options(Rotating_Ascii PRIVATE
    -Wall
    -Wextra
    -ggdb
)
