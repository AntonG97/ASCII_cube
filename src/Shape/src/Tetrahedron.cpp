#include "Tetrahedron.h"

namespace
{
    constexpr int V1 = 0;
    constexpr int V2 = 1;
    constexpr int V3 = 2;
    constexpr int V4 = 3;
}

Tetrahedron::Tetrahedron() :
    verticies_{
        Vec3( 1,  1,  1),
        Vec3(-1, -1,  1),
        Vec3(-1,  1, -1),
        Vec3( 1, -1, -1)
    },
    faces_{
        Face(verticies_[V1], verticies_[V2], verticies_[V3]),
        Face(verticies_[V1], verticies_[V4], verticies_[V2]),
        Face(verticies_[V1], verticies_[V3], verticies_[V4]),
        Face(verticies_[V2], verticies_[V4], verticies_[V3])
    }
{
}
