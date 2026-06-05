#include "Shape.h"

namespace 
{
    constexpr double PI_ = 3.14159265358979323846;
}

Rotation::Angle& Rotation::Angle::operator+=(double rhs) 
{
    angle_ = std::fmod(angle_ + rhs, 2 * PI_);
    return *this;
}

Rotation::Trig& Rotation::Trig::operator+=(const double rhs)
{
    const double angle = rhs;
    cos_ = std::cos(angle);
    sin_ = std::sin(angle);
    return *this;
}
// Updates the rotation matrice
void Rotation::matriceMult()
{
    //Get the latest trigonometic values
    const double cosX = xTrig_.getCos();
    const double sinX = xTrig_.getSin();

    const double cosY = yTrig_.getCos();
    const double sinY = yTrig_.getSin();

    const double cosZ = zTrig_.getCos();
    const double sinZ = zTrig_.getSin();

    //Perform the matrice multiplication
    //And update the rotation matrice
    rMatrice_[0][0] = cosZ*cosY;
	rMatrice_[0][1] = cosZ*sinY*sinX-sinZ*cosX;
	rMatrice_[0][2] = cosZ*sinY*cosX +sinZ*sinX;

	rMatrice_[1][0] = sinZ*cosY;
	rMatrice_[1][1] = sinZ*sinY*sinX+cosZ*cosX;
	rMatrice_[1][2] = sinZ*sinY*cosX-cosZ*sinX;

	rMatrice_[2][0] = -sinY;
	rMatrice_[2][1] = cosY*sinX;
	rMatrice_[2][2] = cosY*cosX;
}
void Rotation::updateRotationMatrice(
    const double incrAngleX,
    const double incrAngleY,
    const double incrAngleZ
    )
{
    //Update each coordinates trigonometic functions
    xTrig_ += xAng_.getAngle();
    yTrig_ += yAng_.getAngle();
    zTrig_ += zAng_.getAngle();

    //Increment the angles
    xAng_ += incrAngleX;
    yAng_ += incrAngleY;
    zAng_ += incrAngleZ;

    //Perfom the matrice multiplication
    //Thereby updating the rotation matrice
    matriceMult();
}