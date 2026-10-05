#include "ArgParser.h"
#include "CLIpc.h"
#include "Rasterizer.h"

int main(int argc, char** argv)
{
    ArgParser args(argc, argv);
    auto shape = args.parseArgs();

    if (!shape)
    {
        return 1;
    }

    CLIpc display(args.IsColorSet());
    Rasterizer rasterizer(*shape, display);
    volatile long x = 0;
    while(1)
    {
        if(x == 0)
        {
            rasterizer.render();
        }
        else
        {
            x = (x + 1) % 1000000;
        }
    }

    return 0;
}