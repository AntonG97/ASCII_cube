#pragma once

#include "Shape.h"

class Cube : public Shape, public Rotation
{
    public:
        Cube();
        void rotate() override;
        void project() override;
        void print() override;
        ~Cube() = default;

    private:
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