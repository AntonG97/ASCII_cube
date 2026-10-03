#include "Angle.h"
#include <cmath>

Angle& Angle::operator+=(const Angle& rhs)
{
	angle_ = fmod(angle_ + rhs.angle_, 2*M_PI);
    return *this;
}

Angle& Angle::operator+=(double rhs)
{
	angle_ = fmod(angle_ + rhs, 2*M_PI);
    return *this;
}

Angle::operator double() const
{
    return angle_;
}  

double Angle::sin() const
{
    return std::sin(angle_);
}

double Angle::cos() const
{
    return std::cos(angle_);
}
