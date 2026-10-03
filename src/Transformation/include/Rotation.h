#pragma once
#include <array>
#include "stdlib.h"
#include "Util.h"
#include "RotationMatrice.h"
#include "Angle.h"

template<std::size_t V>
class Rotation
{
private:
    RotationMatrice rMatrice_;
    const std ::array<Vec3,V> original_;
    Angle ax_;
    Angle ay_;
    Angle az_;
public:
    Rotation<V>(const std::array<Vec3,V>& original);
    void rotate(std::array<Vec3,V>& vectors);
};


template<std::size_t V>
Rotation<V>::Rotation(const std::array<Vec3,V>& original) :
    original_(original),
    rMatrice_(),
    ax_(),
    ay_(),
    az_()
    {

    }

template<std::size_t V>
void Rotation<V>::rotate(
    std::array<Vec3,V>& vectors)
    {
        rMatrice_.set(ax_, ay_, az_);

        for(size_t i = 0; i < V; ++i)
        {
            Vec3 v = original_[i];
            vectors[i].x_ = rMatrice_[0][0] * v.x_ + rMatrice_[0][1] * v.y_ + rMatrice_[0][2] * v.z_;
            vectors[i].y_ = rMatrice_[1][0] * v.x_ + rMatrice_[1][1] * v.y_ + rMatrice_[1][2] * v.z_;
		    vectors[i].z_ = rMatrice_[2][0] * v.x_ + rMatrice_[2][1] * v.y_ + rMatrice_[2][2] * v.z_;
        }

        ax_ += 0.013;
        ay_ += 0.025;
        az_ += 0.026;
    }
   
