#include "Pyramid.h"

namespace
{
    constexpr int V1 = 0;
    constexpr int V2 = 1;
    constexpr int V3 = 2;
    constexpr int V4 = 3;
    constexpr int V5 = 4;
}

Pyramid::Pyramid() :
    verticies_{
        Vec3( 1, -1,  1), // V1
        Vec3(-1, -1,  1), // V2
        Vec3(-1, -1, -1), // V3
        Vec3( 1, -1, -1), // V4
        Vec3( 0,  1,  0)  // V5
    },

    faces_{
        // Bottom
        Face(verticies_[V1], verticies_[V3], verticies_[V2]),
        Face(verticies_[V1], verticies_[V4], verticies_[V3]),

        // Sides
        Face(verticies_[V1], verticies_[V2], verticies_[V5]),
        Face(verticies_[V2], verticies_[V3], verticies_[V5]),
        Face(verticies_[V3], verticies_[V4], verticies_[V5]),
        Face(verticies_[V4], verticies_[V1], verticies_[V5])
    }
{
    // Constructor body
}