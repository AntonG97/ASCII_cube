#pragma once

#include <vector>

#include "Rotation.h"
#include "Projection.h"

class Geometry
{
private:
    Rotation rotation_;
    Projection projection_;
public:
    explicit Geometry(const std::vector<Vec3>& original);
};