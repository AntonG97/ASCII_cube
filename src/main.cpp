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
    volatile long x = 0;
    while(1)
    {
        if(x == 0)
        {
            renderer.render();
        }
        else
        {
            x = (x + 1) % 1000000;
        }
    }

    return 0;
}