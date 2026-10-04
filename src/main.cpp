#include "ArgParser.h"
#include "CLIpc.h"
#include "Renderer.h"

int main(int argc, char** argv)
{
    ArgParser args(argc, argv);
    auto shape = args.parseArgs();

    if (!shape)
    {
        return 1;
    }

    CLIpc display(args.IsColorSet());
    Renderer renderer(*shape, display);
    renderer.render();

    return 0;
}