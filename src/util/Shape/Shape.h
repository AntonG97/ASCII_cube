#include "Vec3.h"
#include <array>
#include "stddef.h"

//Faces contain the index of verticies
//Each face is a triangle, i.e requires the index of 3 verticies
typedef struct Faces
{
    size_t a_;
    size_t b_;
    size_t c_;
};

//Shape define the geometric base of an arbitrary shape
template<size_t V, size_t F>
struct Shape
{
    std::array<Vec3, V> vertices_;
    std::array<Faces, F> faces_;
};
