#pragma once
#include <memory>
#include "Shape.h"

enum class Shape_t : int
{
    Cube = 0,
    Pyramid,
    Octahedron,
    Random
};

namespace ShapeFactory
{
    std::unique_ptr<Shape> create(Shape_t Shape);
}