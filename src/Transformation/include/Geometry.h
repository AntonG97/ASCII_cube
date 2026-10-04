#pragma once

#include "Rotation.h"
#include "Projection.h"

template<std::size_t V>
class Geometry
{
private:
    Rotation<V> rotation_;
    Projection<V> projection_;
    
public:
    Geometry<V>(const std::array<Vec3, V>& original) :
        rotation_(),
        projection_()
        {

        }
};