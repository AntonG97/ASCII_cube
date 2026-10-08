#include <iostream>
#include <charconv>
#include <cstring>
#include <string>
#include "ArgParser.h"
#include "Shape.h"
#include "ShapeFactory.h"


ArgParser::ArgParser(int argc, char** argv) :
    argc_(argc),
    argv_(static_cast<char**>(argv))
    {
        // Constructor body
    }

// Generates a Shape if valid input arguments. Returns nullptr if invalid
std::unique_ptr<Shape> ArgParser::parseArgs()
{
    if(argc_ > 4 || argc_ < 2)
    {
        printHelp();
        return nullptr;
    }

    Shape_t shape = Shape_t::Cube;
    bool shapeIsSet = false;
    bool scaleIsSet = false;

    for(size_t i = 1U; i < argc_; ++i)
    {
        bool isColor = isArgColor(i);
        if(isColor)
        {   
            colorIsSet_ = true;
            continue;
        }

        std::optional<Shape_t> isShape = isArgShape(i);
        if(isShape.has_value())
        {
            if (shapeIsSet)
            {
                printHelp();
                return nullptr;
            }
            shape = isShape.value();
            shapeIsSet = true;
            continue;
        }

        std::optional<int> scale = isArgScale(i);
        if (scale.has_value() && !scaleIsSet)
        {
            scale_ = scale.value();
            scaleIsSet = true;
            continue;
        }

        printHelp();
        return nullptr;
    }

    if (!shapeIsSet)
    {
        printHelp();
        return nullptr;
    }

    return ShapeFactory::create(shape);
}



void ArgParser::printHelp()
{
    std::cout << "### How to start program ###\n\
                  ./<Program> [Shape] [Scale] [-Color]\n\
              [Shape]   = Cube | Octahedron | Tetrahedron | Random\n\
                  [Scale]   = Positive integer (default 20)\n\
                  [-Color]  = Display face color\n";
}

bool ArgParser::isArgColor(size_t index) const
{
    bool isColor = false;

    if(index <= argc_ - 1)
    {
        const std::string input{argv_[index]};

        if(input == "-Color" || input == "-color" ||
           input == "-C" || input == "-c")
        {
            isColor = true;
        }    
    }
    
    return isColor;
}

std::optional<Shape_t> ArgParser::isArgShape(size_t index) const
{
    std::optional<Shape_t> tmp = std::nullopt; 
    
    if(index <= argc_ - 1)
    {
        const std::string input{argv_[index]};

        if(input == "Cube" || input == "cube")
        {
            tmp = Shape_t::Cube;
        }
        if(input == "Octahedron" || input == "octahedron")
        {
            tmp = Shape_t::Octahedron;
        }
        if(input == "Tetrahedron" || input == "tetrahedron")
        {
            tmp = Shape_t::Tetrahedron;
        }
        if(input == "Random" || input == "random")
        {
            tmp = Shape_t::Random;
        }
    }

    return tmp;
}

std::optional<int> ArgParser::isArgScale(size_t index) const
{
    const char* input = argv_[index];
    int scale = 0;
    const char* end = input + std::strlen(input);
    const auto result = std::from_chars(input, end, scale);
    if (result.ec != std::errc{} || result.ptr != end || scale <= 0)
    {
        return std::nullopt;
    }
    return scale;
}
