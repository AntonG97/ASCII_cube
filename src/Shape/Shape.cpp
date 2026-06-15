#include "Shape.h"

namespace 
{
    constexpr double PI_ = 3.14159265358979323846;
}

//Increment angle, cos & sin
Rotation::Trigonometic& Rotation::Trigonometic::operator+=(double rhs)
{
    _cos = std::cos(_angle);
    _sin = std::sin(_angle);
    _angle = std::fmod(_angle + rhs, 2 * PI_);
    return *this;
}

// Updates the rotation matrice
void Rotation::matriceMultiplication()
{
    //Get the latest trigonometic values
    const double cosX = _x.getCos();
    const double sinX = _x.getSin();

    const double cosY = _y.getCos();
    const double sinY = _y.getSin();

    const double cosZ = _z.getCos();
    const double sinZ = _z.getSin();

    //Perform the matrice multiplication
    //updating the rotation matrice
    _rotationMatrice[0][0] = cosZ*cosY;
	_rotationMatrice[0][1] = cosZ*sinY*sinX-sinZ*cosX;
	_rotationMatrice[0][2] = cosZ*sinY*cosX +sinZ*sinX;

	_rotationMatrice[1][0] = sinZ*cosY;
	_rotationMatrice[1][1] = sinZ*sinY*sinX+cosZ*cosX;
	_rotationMatrice[1][2] = sinZ*sinY*cosX-cosZ*sinX;

	_rotationMatrice[2][0] = -sinY;
	_rotationMatrice[2][1] = cosY*sinX;
	_rotationMatrice[2][2] = cosY*cosX;
}
void Rotation::updateRotationMatrice(
    const double incrX,
    const double incrY,
    const double incrZ
    )
{
    //Increment the angles, cos and sin for each coordinate
    _x += incrX;
    _y += incrY;
    _z += incrZ;

    //Perfom the matrice multiplication
    //Thereby updating the rotation matrice
    matriceMultiplication();
}