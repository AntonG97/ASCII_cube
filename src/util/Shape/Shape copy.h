#include "StaticContainer.h"

template<size_t V, size_t F>
struct Shape
{
    StaticVector<Vec3, V> vertices;
    StaticVector<Faces, F> faces;
};

//TODO: Faces contain index to verticies!!