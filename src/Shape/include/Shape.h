#pragma once
#include <vector>

#include "Util.h"

// Shape interface
struct Shape
{
    virtual ~Shape() = default;
    virtual std::vector<Vec3>& getVertices() = 0;
    virtual const std::vector<Vec3>& getVertices() const = 0;
    virtual const std::vector<Face>& getFaces() const = 0;
};
