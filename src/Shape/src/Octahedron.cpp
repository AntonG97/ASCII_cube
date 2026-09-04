#include "Octahedron.h"

namespace
{
    constexpr int V1 = 0;
    constexpr int V2 = 1;
    constexpr int V3 = 2;
    constexpr int V4 = 3;
    constexpr int V5 = 4;
    constexpr int V6 = 5;
}

Octahedron::Octahedron() :
    verticies_{
        Vec3( 1,  0,  0), // V1
        Vec3(-1,  0,  0), // V2
        Vec3( 0,  1,  0), // V3
        Vec3( 0, -1,  0), // V4
        Vec3( 0,  0,  1), // V5
        Vec3( 0,  0, -1)  // V6
    },

    faces_{
        // Upper half
        Face(verticies_[V1], verticies_[V3], verticies_[V5]),
        Face(verticies_[V3], verticies_[V2], verticies_[V5]),
        Face(verticies_[V2], verticies_[V4], verticies_[V5]),
        Face(verticies_[V4], verticies_[V1], verticies_[V5]),

        // Lower half
        Face(verticies_[V1], verticies_[V6], verticies_[V3]),
        Face(verticies_[V3], verticies_[V6], verticies_[V2]),
        Face(verticies_[V2], verticies_[V6], verticies_[V4]),
        Face(verticies_[V4], verticies_[V6], verticies_[V1])
    }
{
}