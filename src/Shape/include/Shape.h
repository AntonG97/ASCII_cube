#pragma once
#include <array>

#include "Util.h"
#include "Cube.h"
#include "Octahedron.h"
#include "Pyramid.h"

// Shape interface
struct Shape
{
    public: 
        virtual ~Shape() = default;
};
