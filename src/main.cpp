#include "ArgParser.h"
#include "CLIpc.h"
#include "InputParser.h"
#include "Renderer.h"

#include <csignal>
#include <chrono>
#include <thread>

namespace
{
    volatile std::sig_atomic_t interrupted = 0;

    void handleSignal(int)
    {
        interrupted = 1;
    }
}

int main(int argc, char** argv)
{
    ArgParser args(argc, argv);
    auto shape = args.parseArgs();

    if (!shape)
    {
        return 1;
    }

    CLIpc display(args.IsColorSet());
    Renderer renderer(*shape, display, args.GetScale());

    std::signal(SIGINT, handleSignal);
    while (interrupted == 0)
    {
        renderer.render();
        if (InputParser::exit_program())
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(18500));
    }

    return 0;
}