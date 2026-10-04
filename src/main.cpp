#include "ArgParser.h"
#include "Geometry.h"
#include "Shapes.h"
int main(int argc, char** argv)
{
    ArgParser args(argc, argv);
    std::unique_ptr<Shape> shape = args.parseArgs();

    if (!shape)
    {
        return 1;
    }

    Geometry geometry(shape->getVertices());

    return 0;
}