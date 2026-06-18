#include "Shape.h"

class ShapeFactory
{
public:
        template<size_t V, size_t F>
        static Shape<V,F> createCube();
};


