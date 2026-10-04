#include "Projection.h"

void Projection::project(std::vector<Vec3>& vectors) const
{
    for (Vec3& vertex : vectors)
    {
        vertex.z_ += camera_distance;
        if (vertex.z_ > 0.0)
        {
            vertex.x_ = (vertex.x_ * focal_length) / vertex.z_;
            vertex.y_ = (vertex.y_ * focal_length) / vertex.z_;
        }
    }
}