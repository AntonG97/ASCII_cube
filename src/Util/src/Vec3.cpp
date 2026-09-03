#include "Vec3.h"
#include <math.h>

double Vec3::dot(const Vec3& rhs) const
{
    return x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_;
}

Vec3 Vec3::cross(const Vec3& rhs) const
{
    const double x = y_ * rhs.z_ - z_ - rhs.y_;
    const double y = z_ * rhs.x_ - x_ * rhs.z_;
    const double z = x_ * rhs.y_ - y_ * rhs.x_;
    return Vec3{x,y,z};
}

namespace
{
    constexpr double EPSILON = 1e-6;    
}

bool Vec3::operator==(const Vec3& rhs) const
{
    return  fabs(x_ - rhs.x_) < EPSILON &&
            fabs(y_ - rhs.y_) < EPSILON &&
            fabs(z_ - rhs.z_) < EPSILON;
}

bool Vec3::operator!=(const Vec3& rhs) const
{
    return !(*this == rhs);
}

Vec3 Vec3::operator+(const Vec3& rhs) const
{
   return Vec3{
        x_ + rhs.x_,
        y_ + rhs.y_,
        z_ + rhs.z_
   }; 
}

Vec3 Vec3::operator-(const Vec3& rhs) const
{
   return Vec3{
        x_ - rhs.x_,
        y_ - rhs.y_,
        z_ - rhs.z_
   }; 
}

Vec3 Vec3::operator*(double scalar) const
{
   return Vec3{
        x_ * scalar,
        y_ * scalar,
        z_ * scalar
   }; 
}

Vec3 Vec3::operator/(double scalar) const
{
   return Vec3{
        x_ / scalar,
        y_ / scalar,
        z_ / scalar
   }; 
}

Vec3& Vec3::operator+=(const Vec3& rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;

    return *this;
}

Vec3& Vec3::operator-=(const Vec3& rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;

    return *this;
}

Vec3& Vec3::operator*=(const Vec3& rhs)
{
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    z_ *= rhs.z_;

    return *this;
}

Vec3& Vec3::operator/=(const Vec3& rhs) 
{
    x_ /= rhs.x_;
    y_ /= rhs.y_;
    z_ /= rhs.z_;

    return *this;
}