#pragma once

#include "Shape.h"

struct Tetrahedron : public Shape
{
    std::vector<Vec3> verticies_;
    std::vector<Face> faces_;

    Tetrahedron();
    std::vector<Vec3>& getVertices() override { return verticies_; }
    const std::vector<Vec3>& getVertices() const override { return verticies_; }
    const std::vector<Face>& getFaces() const override { return faces_; }
};
