#pragma once

#include "Vec3.h"
#include "Face.h"

// Shape interface
class Shape
{
    public: 
        virtual void init() = 0; 
        virtual ~Shape() = default;
};
