#include "Cube.h"

Cube::Cube() : _original_cube{
            Vector( 1, -1,  1 ),    //A
            Vector( -1, -1,  1 ),   //B
            Vector( -1,  1,  1 ),   //C
            Vector(  1,  1,  1 ),   //D
            Vector(  1, -1, -1 ),   //E
            Vector( -1, -1, -1 ),   //F
            Vector( -1,  1, -1 ),   //G
            Vector(  1,  1, -1 )    //H 
            }, 
            _cube_rotated{
            Vector( 1, -1,  1 ),    //A
            Vector( -1, -1,  1 ),   //B
            Vector( -1,  1,  1 ),   //C
            Vector(  1,  1,  1 ),   //D
            Vector(  1, -1, -1 ),   //E
            Vector( -1, -1, -1 ),   //F
            Vector( -1,  1, -1 ),   //G
            Vector(  1,  1, -1 )    //H   
            },
            faces{
            { &_cube_rotated[0], &_cube_rotated[3], &_cube_rotated[4], &_cube_rotated[7] }, // A D E H
            { &_cube_rotated[1], &_cube_rotated[0], &_cube_rotated[5], &_cube_rotated[4] }, // B A F E
            { &_cube_rotated[2], &_cube_rotated[1], &_cube_rotated[6], &_cube_rotated[5] }, // C B G F
            { &_cube_rotated[3], &_cube_rotated[2], &_cube_rotated[7], &_cube_rotated[6] }, // D C H G
            { &_cube_rotated[1], &_cube_rotated[2], &_cube_rotated[0], &_cube_rotated[3] }, // B C A D
            { &_cube_rotated[4], &_cube_rotated[7], &_cube_rotated[5], &_cube_rotated[6] }  // E H F G
            }, 
            _nrOfVertices(
                sizeof(_original_cube) / sizeof(_original_cube[0])
            )

            {
                //Constructor body
            }

////////////////////////////// Public methods //////////////////////////
void Cube::rotate()
{
    const Vector* vPtr;
    updateRotationMatrice();
    //const Vector xCoordRotated;

    /* Rotate each vertice of the cube */
    for(size_t i{0}; i < _nrOfVertices; i++)
    {
        vPtr = &_original_cube[i];

        _cube_rotated[i].setX(4);
    }
    
    
}

void Cube::project()
{

}
void Cube::print(){

}

////////////////////////////// Private methods //////////////////////////
void Cube::drawTriangle(Vector a, Vector b,Vector c, char ascii)
{
    
}
void Cube::drawFlatTop(Vector a,Vector b, Vector c, char ascii)
{

}
void Cube::drawFlatBot(Vector a,Vector b, Vector c, char ascii)
{

}
Vector Cube::nearX(Vector a, Vector b)
{

}
Vector Cube::nearY(Vector a, Vector b)
{

}
void Cube::checkBnd(int *y, int *x)
{

}
void Cube::checkVectorBnd(Vector *pt)
{

}
int Cube::isFlat(Vector a, Vector b, Vector c)
{

}
double Cube::getSlope(Vector a, Vector b)
{

}
