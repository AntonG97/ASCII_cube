#pragma once
#include "Shape.h"

struct Cube : public Shape
{
    // Members
    std::array<Vec3, 8> verticies_;
    std::array<Face, 12> faces_;

    // Constructor
    Cube();
};