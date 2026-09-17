cmake_minimum_required(VERSION 3.15)

set(CLI_Parser_Src
    src/ArgParser.cpp
    src/ShapeFactory.cpp
    )

add_library(CLI_Parser
    STATIC
    ${CLI_Parser_Src}   
    )

target_link_libraries(CLI_Parser
    PUBLIC
    Shape
    )

target_include_directories(CLI_Parser
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
