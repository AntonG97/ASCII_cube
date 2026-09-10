cmake_minimum_required(VERSION 3.15)

add_executable(Rotating_Ascii main.cpp)

set_target_properties(Rotating_Ascii PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_subdirectory(Util)
add_subdirectory(Shape)
add_subdirectory(CLI_Parser)

target_link_libraries(Rotating_Ascii
    Util
    Shape
    CLI_Parser
    )

target_compile_options(Rotating_Ascii PRIVATE
    -Wall
    -Wextra
    -ggdb
)
