#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Shape.h"
#include "ParsedPacket.h"

enum class Shape_t;

class ArgParser
{
private:
    std::vector<std::string> args;
public:
    ArgParser(const int argc, const char* const* argv);
    ParsedPacket parse();
    
private:
    void printHelpAndExit()const;
    bool isArgColor(const std::string input) const;
    std::optional<Shape_t> isArgShape(const std::string input) const;
    std::optional<int> isArgScale(const std::string input) const;
    std::optional<Resolution> isArgResolution(const std::string input)const;
};
