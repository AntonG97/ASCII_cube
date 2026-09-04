#include "Cube.h"

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
};

Cube::Cube() :
    verticies_{
        Vec3( 1, -1,  1), // V1
        Vec3(-1, -1,  1), // V2
        Vec3(-1,  1,  1), // V3
        Vec3( 1,  1,  1), // V4
        Vec3( 1, -1, -1), // V5
        Vec3(-1, -1, -1), // V6
        Vec3(-1,  1, -1), // V7
        Vec3( 1,  1, -1)  // V8
    },
    faces_{
        // Front
        Face(verticies_[V1], verticies_[V2], verticies_[V3]),
        Face(verticies_[V1], verticies_[V3], verticies_[V4]),

        // Back
        Face(verticies_[V5], verticies_[V7], verticies_[V6]),
        Face(verticies_[V5], verticies_[V8], verticies_[V7]),

        // Left
        Face(verticies_[V2], verticies_[V6], verticies_[V7]),
        Face(verticies_[V2], verticies_[V7], verticies_[V3]),

        // Right
        Face(verticies_[V1], verticies_[V4], verticies_[V8]),
        Face(verticies_[V1], verticies_[V8], verticies_[V5]),

        // Top
        Face(verticies_[V3], verticies_[V7], verticies_[V8]),
        Face(verticies_[V3], verticies_[V8], verticies_[V4]),

        // Bottom
        Face(verticies_[V1], verticies_[V5], verticies_[V6]),
        Face(verticies_[V1], verticies_[V6], verticies_[V2])
    }
    {
        // Constructor Body
    }
