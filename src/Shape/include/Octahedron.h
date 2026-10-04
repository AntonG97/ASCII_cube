#pragma once
#include "Shape.h"

struct Octahedron : public Shape
{
    std::vector<Vec3> verticies_;
    std::vector<Face> faces_;

    Octahedron();
    std::vector<Vec3>& getVertices() override { return verticies_; }
    const std::vector<Vec3>& getVertices() const override { return verticies_; }
    const std::vector<Face>& getFaces() const override { return faces_; }
};