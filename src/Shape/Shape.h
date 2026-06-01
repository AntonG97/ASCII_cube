#pragma once

#include "Vector.h"

class Rotation
{
    public:
        Rotation() : xCoordAng(0), yCoordAng(0), zCoordAng(0), rotationMatrice{} {}
        void virtual rotate() = 0;
        virtual ~Rotation() = default;

    protected:
        double xCoordAng;
        double yCoordAng;
        double zCoordAng;
        double rotationMatrice[3][3];

        void updateRotationMatrice();
};

class Shape
{
    public: 
        virtual void project() = 0;
        virtual void print() = 0;
        virtual ~Shape() = default;
};
