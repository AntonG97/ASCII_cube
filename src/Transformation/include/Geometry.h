#pragma once

#include <vector>

#include "Rotation.h"
#include "Projection.h"

class Geometry
{
private:
    std::vector<Vec3>& vertices_;
    Rotation rotation_;
    Projection projection_;
public:
    explicit Geometry(std::vector<Vec3>& vertices);
    void transform();
};