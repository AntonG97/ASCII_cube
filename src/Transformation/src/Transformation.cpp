#include "Transformation.h"

Transformation::Transformation(const std::vector<Vec3>& original) :
	rotation_(original),
	projection_()
{

}

void Transformation::transform(std::vector<Vec3>& vertecies)
{
	rotation_.rotate(vertecies);
	projection_.project(vertecies);
}