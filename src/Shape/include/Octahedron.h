#pragma once
#include "Shape.h"

struct Octahedron : public Shape
{
    std::array<Vec3,6> verticies_;
    std::array<Face,8> faces_;

    Octahedron();
};