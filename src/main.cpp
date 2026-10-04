#include "ArgParser.h"
#include "Geometry.h"
#include "Shapes.h"
int main(int argc, char** argv)
{
    ArgParser args(argc, argv);
    std::unique_ptr<Shape> shape = args.parseArgs();
    Geometry<10>(shape.verticies_);

    return 0;
}