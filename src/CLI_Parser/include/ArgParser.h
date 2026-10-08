#pragma once

#include <memory>
#include <optional>

#include "Shape.h"

enum class Shape_t;

class ArgParser
{
private:
    const int argc_;
    char** const argv_;
    bool colorIsSet_ = false;
    int scale_ = 20;
public:
    ArgParser(int argc, char** argv);
    std::unique_ptr<Shape> parseArgs();
    bool IsColorSet() const { return colorIsSet_; }
    int GetScale() const { return scale_; }

private:
    void printHelp();
    bool isArgColor(size_t index) const;
    std::optional<Shape_t> isArgShape(size_t index) const;
    std::optional<int> isArgScale(size_t index) const;
};