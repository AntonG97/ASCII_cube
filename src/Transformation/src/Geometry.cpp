#include "Geometry.h"

Geometry::Geometry(std::vector<Vec3>& vertices) :
	vertices_(vertices),
	rotation_(vertices),
	projection_()
{
}

void Geometry::transform()
{
	rotation_.rotate(vertices_);
	projection_.project(vertices_);
}