cmake_minimum_required(VERSION 3.15)

# Declares the project name
project(ascii_cube)

# Create an executable target from the source file
add_executable(ascii_cube ascii_cube.c)

# Link with math library
target_link_libraries(ascii_cube PRIVATE m)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -ggdb -O4")

