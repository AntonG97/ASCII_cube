#pragma once
#include <vector>

#include "Util.h"

class Projection
{
private:
    const double focal_length = 1.0;
public:
    void project(std::vector<Vec3>& vectors) const;
};
