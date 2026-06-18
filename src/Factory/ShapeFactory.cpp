#include "ShapeFactory.h"

namespace
{

}
namespace ShapeFactory
{

    template<uint16_t V, uint16_t F>
    Shape<V,F> createShape(ShapeType t)
    {
        switch(t)
        {
            case ShapeType::Cube: return Shape<8, 12>;  
            case ShapeType::Triangle: return Shape<5,5>;
        }
    }
}
