#include "Vec3.h"
#include <array>
#include <cstdint>

//Faces contain the index of verticies
//Each face is a triangle, i.e requires the index of 3 verticies
typedef struct Faces
{
    uint16_t a_, b_, c_;
};

//Shape define the geometric base of an arbitrary shape

//TODO: Fix so that I do not require templates?
// Can I set the std::array size directly when creating the obecjt?
template<uint16_t V, uint16_t F>
struct Shape
{
    std::array<Vec3, V> vertices_;
    std::array<Faces, F> faces_;
};
