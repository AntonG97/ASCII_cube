#pragma once
#include <array>

#include "Shape.h"

namespace
{
    constexpr int V1 = 0;
    constexpr int V2 = 1;
    constexpr int V3 = 2;
    constexpr int V4 = 3;
    constexpr int V5 = 4;
    constexpr int V6 = 5;
    constexpr int V7 = 6;
    constexpr int V8 = 7;
}

struct Cube : Shape
{
    // Members

    std::array<Vec3, 8> verticies_;
    std::array<Face, 12> faces_;

    // Constructor

    Cube() :
        verticies_{
            Vec3(  1, -1,  1), //A
            Vec3( -1, -1,  1), //B
            Vec3( -1,  1,  1), //C
            Vec3(  1,  1,  1), //D
            Vec3(  1, -1, -1), //E
            Vec3( -1, -1, -1), //F
            Vec3( -1,  1, -1), //G
            Vec3(  1,  1, -1), //H
        },
        faces_{
            Face(verticies_[0], verticies_[1], verticies_[2]),
        }

        {
            // Constructor Body
        }
};