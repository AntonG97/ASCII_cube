#pragma once
#include "stdlib.h"

class Angle;

struct RotationMatrice
{
private:
    double m_[3][3]; 
public:
    constexpr RotationMatrice();
    double* operator[](std::size_t index);
    const double* operator[](std::size_t index) const;
    void setMatrice(
        const Angle& x,
        const Angle& y,
        const Angle& z
    );
};
