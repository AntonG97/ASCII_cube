#include "Transformation.h"

Transformation::Transformation(std::vector<Vec3>& vertices) :
	vertices_(vertices),
	rotation_(vertices),
	projection_()
{
}

void Transformation::transform()
{
	rotation_.rotate(vertices_);
	projection_.project(vertices_);
}