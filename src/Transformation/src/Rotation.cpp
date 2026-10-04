#include "Rotation.h"

Rotation::Rotation(const std::vector<Vec3>& original) :
    rMatrice_(),
    original_(original),
    ax_(),
    ay_(),
    az_()
{
}

void Rotation::rotate(std::vector<Vec3>& vectors)
{
    rMatrice_.set(ax_, ay_, az_);
    for (std::size_t i = 0; i < original_.size(); ++i)
    {
        const Vec3& vertex = original_[i];
        vectors[i].x_ = rMatrice_[0][0] * vertex.x_ + rMatrice_[0][1] * vertex.y_ + rMatrice_[0][2] * vertex.z_;
        vectors[i].y_ = rMatrice_[1][0] * vertex.x_ + rMatrice_[1][1] * vertex.y_ + rMatrice_[1][2] * vertex.z_;
        vectors[i].z_ = rMatrice_[2][0] * vertex.x_ + rMatrice_[2][1] * vertex.y_ + rMatrice_[2][2] * vertex.z_;
    }

    ax_ += 0.013;
    ay_ += 0.025;
    az_ += 0.026;
}