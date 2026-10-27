#include <iostream>
#include <string>
#include <regex>
#include <cctype>
#include "ArgParser.h"
#include "Shape.h"
#include "ShapeFactory.h"

ArgParser::ArgParser(const int argc, const char* const* argv) :
    args()
    {
    /*
     if(argc > 5)
        {
            printHelpAndExit();
        }
       args.reserve(argc);
    */
        for(int i = 0; i < argc; ++i)
        {
            args.emplace_back(argv[i]);
        }
    }

// Generates a ParsedPackage object.
ParsedPacket ArgParser::parse()
{
    ParsedPacket packet;

    if((args.size()) % 2 == 0)
    {
        // Even number of args, not valid.
        printHelpAndExit();
    }
    
    Shape_t shape = Shape_t::Cube;
    for(auto It = args.begin() + 1; It + 1 < args.end(); It += 2)
    {
        const std::string Arg_Pair = *It + " " + *(It+1);
        const bool isColor = isArgColor(Arg_Pair);
        if(isColor)
        {
            if(packet.isColorSet_ == static_cast<bool>(Status::NOT_SET))
            {   
                packet.isColorSet_ = true;
            }
            else
            {
                printHelpAndExit();
            }
        }

        std::optional<Shape_t> isShape = isArgShape(Arg_Pair);
        if(isShape.has_value())
        {
            if (packet.shape_ == nullptr)
            {
                packet.shape_ = ShapeFactory::create(isShape.value());
            }
            else
            {
                printHelpAndExit();
            }
        }

        std::optional<int> scale = isArgScale(Arg_Pair);
        if (scale.has_value())
        {
            if(packet.scale_ == static_cast<int>(Status::NOT_SET))
            {
                packet.scale_ = scale.value();
            }
            else
            {
                printHelpAndExit();
            }
        }
        
        std::optional<Resolution> res = isArgResolution(Arg_Pair);
        if(res.has_value())
        {
            if(packet.resolution_.height_ == static_cast<int>(Status::NOT_SET) &&
               packet.resolution_.width_  == static_cast<int>(Status::NOT_SET))
            {
                packet.resolution_ = res.value();
            }
            else
            {
                printHelpAndExit();
            }
        }

        if( !isColor && !isShape.has_value() && 
            !scale.has_value() && !res.has_value())
            {

                printHelpAndExit();
            }
    }

    if(packet.scale_ == static_cast<int>(Status::NOT_SET))
    {
        packet.scale_ = 20;
    }

    if(packet.shape_ == nullptr)
    {
        packet.shape_ = ShapeFactory::create(Shape_t::Cube);
    }    

    if(packet.isColorSet_ == static_cast<bool>(Status::NOT_SET))
    {
        packet.isColorSet_ = false;
    }

    if(packet.resolution_.height_ == static_cast<int>(Status::NOT_SET) &&
       packet.resolution_.width_ == static_cast<int>(Status::NOT_SET))
    {
        packet.resolution_.height_  = 20;
        packet.resolution_.width_   = 40; 
    }

    return packet;
}

void ArgParser::printHelpAndExit() const
{
    std::cout << "\
        ### How to start program ###\n\
        ./<Program> [-Shape <shape>] [(-Scale | -S) <scale>] [-Color | -C <status>] [-Resolution <width>x<height>]\n\
        [-Shape <shape>]    <shape> = Cube | Octahedron | Tetrahedron | Random. (Default Cube)\n\
        [-Scale <scale>]    <scale> = Positive integer. (Default 20)\n\
        [-Color | -C <status>]  <status> = on | off. (Default off)\n\
        [-Resolution <width>x<height>] <width> <height> = Positive integers. (Default 40x20)\n";
    exit(static_cast<int>(Status::INCORRECT_ARGS));
}

bool ArgParser::isArgColor(const std::string input) const
{
    bool isColor = false;
    const std::regex pattern(R"(-?[Cc](?:olor)?\s+([Oo]n|[Ff]alse))");
    std::smatch match;
    if(std::regex_match(input, match, pattern))
    {
       std::string arg = match[1].str();
       toLowerCase(arg);
       isColor = (arg == "on") ? true : false; 
    }
    
    return isColor;
}

std::optional<Shape_t> ArgParser::isArgShape(const std::string input) const
{
    std::optional<Shape_t> tmp = std::nullopt; 
    const std::regex pattern(R"(\s*-?[Ss]hape\s+(\w+))");
    std::smatch match;

    if(std::regex_match(input, match, pattern))
    {
        std::string shape = match[1].str();
        toLowerCase(shape);
        
        if(shape == "cube")
        {
            tmp = Shape_t::Cube;
        }
        else if(shape == "octahedron")
        {
            tmp = Shape_t::Octahedron;
        }
        else if(shape == "tetrahedron")
        {
            tmp = Shape_t::Tetrahedron;
        }
        else if(shape == "random")
        {
            tmp = Shape_t::Random;
        }
    }

    return tmp;
}

std::optional<int> ArgParser::isArgScale(const std::string input) const
{
    std::optional<int> scale = std::nullopt;
    const std::regex pattern(R"(-?[Ss]cale\s+(\d+))");
    std::smatch match;

    if(std::regex_search(input, match, pattern))
    {
        scale.emplace(std::stoi(match[1].str()));
    }

    return scale;
}

std::optional<Resolution> ArgParser::isArgResolution(const std::string input) const
{
    std::optional<Resolution> res = std::nullopt;
    const std::regex pattern(R"(-[Rr]esolution\s+(\d+)x(\d+))");
    std::smatch match;

    if (std::regex_search(input, match, pattern))
    {
        int width = std::stoi(match[1].str());
        int height = std::stoi(match[2].str());

        res.emplace(width, height);
    }
    
    return res;
}

void ArgParser::toLowerCase(std::string &input) const
{
    for(char& ch : input)
    {
        const int char_int = std::tolower(static_cast<unsigned char>(ch));
        ch = static_cast<char>(char_int);
    }
}
