#pragma once
#include <cstddef>
#include <vector>

#include "Util.h"
#include "RotationMatrice.h"
#include "Angle.h"

class Rotation
{
private:
    RotationMatrice rMatrice_;
    const std::vector<Vec3> original_;
    Angle ax_;
    Angle ay_;
    Angle az_;
public:
    explicit Rotation(const std::vector<Vec3>& original);
    void rotate(std::vector<Vec3>& vectors);
};
   
