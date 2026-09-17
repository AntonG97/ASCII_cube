#pragma once

#include <memory>
#include <optional>

class Shape;
enum class Shape_t;

class ArgParser
{
private:
    const int argc_;
    char** const argv_;
    bool colorIsSet_ = false;
public:
    ArgParser(int argc, char** argv);
    std::unique_ptr<Shape> parseArgs();
    bool IsColorSet() const {return colorIsSet_;}

private:
    void printHelp();
    bool isArgColor(size_t index) const;
    std::optional<Shape_t> isArgShape(size_t index) const;
};