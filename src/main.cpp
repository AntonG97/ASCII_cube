#include "ArgParser.h"
#include "Geometry.h"
#include "Shapes.h"
int main(int argc, char** argv)
{
    ArgParser args(argc, argv);
    auto shape = args.parseArgs();

    Geometry geometry(shape->getVertices());

    return 0;
}