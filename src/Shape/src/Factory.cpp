#include <cstdlib>
#include "Factory.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Octahedron.h"


namespace
{
    constexpr int Mod = static_cast<int>(Shape_t::Random);

    Shape_t Gen_Random()
    {
        srand(time(0));
        int nb = rand() % Mod;
        return static_cast<Shape_t>(nb);
    }
}

std::unique_ptr<Shape> ShapeFactory::create(Shape_t Type)
{
    std::unique_ptr<Shape> tmp = nullptr;

    switch(Type)
    {
        case Shape_t::Cube:         tmp = std::make_unique<Cube>(); break;
        case Shape_t::Pyramid:      tmp = std::make_unique<Pyramid>(); break;
        case Shape_t::Octahedron:   tmp = std::make_unique<Octahedron>(); break;
        case Shape_t::Random:       
        default: break;
    }
    return tmp;
}