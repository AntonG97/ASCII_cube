cmake_minimum_required(VERSION 3.15)

# Declares the project name
project(ascii_cube)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

# Create an executable target from the source files
add_executable(ascii_cube main.cpp ${SOURCES})

#Tell compiler to search recursively for .h files in /src
target_include_directories(ascii_cube PRIVATE
    src/Shape
    src/Shape/Cube
    src/Vector
    src/CLI
)

# Link with math library
target_link_libraries(ascii_cube PRIVATE m )

#Compile flags
target_compile_options(ascii_cube PRIVATE
    -Wall
    -Wextra
    -ggdb
    -O4
)

