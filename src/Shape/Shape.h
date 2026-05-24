#pragma once

#include "Vector.h"

class Shape
{
    public: 

        virtual void rotate() = 0;
        virtual void project() = 0;
        virtual void print() = 0;

        virtual ~Shape() = default;

    protected: 
        double angleX;
        double angleY;
        double angleZ; 
        double rotationMatrice[3][3];

        void updateRotationMatrice();
};

class Cube : public Shape
{
    public:
        Cube();
        void rotate();
        void project();
        void print();

    private:

        void drawTriangle(struct vector a, struct vector b, struct vector c, char ascii);
        void drawFlatTop(struct vector a, struct vector b, struct vector c, char ascii);
        void drawFlatBot(struct vector a, struct vector b, struct vector c, char ascii);
        struct vector nearX(struct vector a, struct vector b);
        struct vector nearY(struct vector a, struct vector b);

        void checkBnd(int *y, int *x);
        void checkVectorBnd(struct vector *pt);
        int isFlat(struct vector a, struct vector b, struct vector c);
        double getSlope(struct vector a, struct vector b);

        struct face
        {
            struct Vector *TL;
            struct Vector *TR;
            struct Vector *BL;
            struct Vector *BR;
        } faces[6] = {
            { &_cube_rotated[0], &_cube_rotated[3], &_cube_rotated[4], &_cube_rotated[7] }, // A D E H
            { &_cube_rotated[1], &_cube_rotated[0], &_cube_rotated[5], &_cube_rotated[4] }, // B A F E
            { &_cube_rotated[2], &_cube_rotated[1], &_cube_rotated[6], &_cube_rotated[5] }, // C B G F
            { &_cube_rotated[3], &_cube_rotated[2], &_cube_rotated[7], &_cube_rotated[6] }, // D C H G
            { &_cube_rotated[1], &_cube_rotated[2], &_cube_rotated[0], &_cube_rotated[3] }, // B C A D
            { &_cube_rotated[4], &_cube_rotated[7], &_cube_rotated[5], &_cube_rotated[6] }  // E H F G
        };

        const Vector _original_cube[8] = {
            {  1, -1,  1 },   //A
            { -1, -1,  1 },   //B
            { -1,  1,  1 },   //C
            {  1,  1,  1 },   //D
            {  1, -1, -1 },   //E
            { -1, -1, -1 },   //F
            { -1,  1, -1 },   //G
            {  1,  1, -1 }    //H
        };
        
        Vector _cube_rotated[8] = {
            {  1, -1,  1 },   //A
            { -1, -1,  1 },   //B
            { -1,  1,  1 },   //C
            {  1,  1,  1 },   //D
            {  1, -1, -1 },   //E
            { -1, -1, -1 },   //F
            { -1,  1, -1 },   //G
            {  1,  1, -1 }    //H
        };
};
