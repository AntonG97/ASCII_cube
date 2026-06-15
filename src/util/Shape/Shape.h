#include "StaticContainer.h"
#include "Vec3.h"

//Faces contain the index of verticies
//Each face is a triangle, i.e requires the index of 3 verticies
typedef struct Faces
{
    size_t A;
    size_t B;
    size_t C;
};

//Shape define the geometric base of an arbitrary shape
template<size_t V, size_t F>
struct Shape
{
    StaticVector<Vec3, V> vertices;
    StaticVector<Faces, F> faces;
};
