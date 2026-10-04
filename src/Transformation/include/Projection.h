#pragma once
#include <array>
#include "stdlib.h"
#include "Util.h"

template<std::size_t V>
class Projection
{
private:
    const double focal_length = 1.0;
public:
    Projection<V>() {};
    void project(std::array<Vec3, V>& vectors) const;
};

template <std::size_t V>
inline void Projection<V>::project(std::array<Vec3, V> &vectors) const
{
    for(Vec3& v : vectors)
    {
        if(v.z_ != 0.0)
        {
            v.x_ = (v.x_ * focal_length) / v.z_;
            v.y_ = (v.y_ * focal_length) / v.z_;
        }
    }
}
