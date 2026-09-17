#include <iostream>
#include <cstring>
#include "ArgParser.h"
#include "Shape.h"
#include "ShapeFactory.h"


//DBG remove
#include <iostream>

ArgParser::ArgParser(int argc, char** argv) :
    argc_(argc),
    argv_(static_cast<char**>(argv))
    {
        // Constructor body
    }

// Generates a Shape if valid input arguments. Returns nullptr if invalid
std::unique_ptr<Shape> ArgParser::parseArgs()
{
    if(argc_ > 3 || argc_ < 2) 
    {
        printHelp();
        return nullptr;
    }

    Shape_t shape = Shape_t::Cube;

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
            shape = isShape.value();   
        }
    }

    return ShapeFactory::create(shape);
}



void ArgParser::printHelp()
{
    std::cout << "### How to start program ###\n\
                  ./<Program> [Shape] [-Color]\n\
                  [Shape]   = Cube | Pyramid | Octahedron | Random\n\
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
            std::cout << "Gen Cube\n";
        }
        if(input == "Pyramid" || input == "pyramid")
        {
            tmp = Shape_t::Pyramid;
            std::cout << "Gen Pyr\n";
        }   
        if(input == "Octahedron" || input == "octahedron")
        {
            tmp = Shape_t::Octahedron;
            std::cout << "Gen Octal\n";
        }
        if(input == "Random" || input == "random")
        {
            tmp = Shape_t::Random;
            std::cout << "Gen Rand\n";
        }
    }

    return tmp;
}
