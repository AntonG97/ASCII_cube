#pragma once

#include <vector>

#include "Rotation.h"
#include "Projection.h"

class Transformation
{
private:
    std::vector<Vec3>& vertices_;
    Rotation rotation_;
    Projection projection_;
public:
    explicit Transformation(std::vector<Vec3>& vertices);
    void transform();
};