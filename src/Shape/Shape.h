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

        virtual void updateRotationMatrice() = 0;
};

class Shape
{
    public: 
        virtual void project() = 0;
        virtual void print() = 0;
        virtual ~Shape() = default;
};

class Cube : public Shape, public Rotation
{
    public:
        Cube();
        void rotate() override;
        void project() override;
        void print() override;
        ~Cube();

    private:
        void updateRotationMatrice() override;
        void drawTriangle(Vector a, Vector b, Vector c, char ascii);
        void drawFlatTop( Vector a,  Vector b,  Vector c, char ascii);
        void drawFlatBot( Vector a,  Vector b,  Vector c, char ascii);
        Vector nearX( Vector a,  Vector b);
        Vector nearY( Vector a,  Vector b);
        void checkBnd(int *y, int *x);
        void checkVectorBnd( Vector *pt);
        int isFlat( Vector a,  Vector b,  Vector c);
        double getSlope( Vector a,  Vector b);

        struct CubeFace
        {
            struct Vector *TL;
            struct Vector *TR;
            struct Vector *BL;
            struct Vector *BR;
        };
        const Vector _original_cube[8];
        Vector _cube_rotated[8];
        struct CubeFace faces[6];
};
