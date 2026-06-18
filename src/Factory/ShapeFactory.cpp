#include "ShapeFactory.h"


template<size_t V, size_t F>
Shape<V,F> ShapeFactory::createCube()
{
    static Shape<V,F> cube;

    return cube;

}