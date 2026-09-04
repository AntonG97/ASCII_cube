#pragma once
#include "Shape.h"

struct Pyramid : public Shape
{
    std::array<Vec3,5> verticies_;
    std::array<Face,6> faces_;

    Pyramid();
};
