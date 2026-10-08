#pragma once

#include <vector>

#include "Rotation.h"
#include "Projection.h"

class Transformation
{
private:
    Rotation rotation_;
    Projection projection_;
public:
    explicit Transformation(const std::vector<Vec3>& original);
    void transform(std::vector<Vec3>& vertecies);
};