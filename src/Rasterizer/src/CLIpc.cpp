#include "CLIpc.h"

#include <iostream>

namespace
{
    constexpr std::size_t DisplayWidth = 80;
    constexpr std::size_t DisplayHeight = 40;

    const char* colorFor(char pixel)
    {
        switch (pixel)
        {
            case '#': return "\033[91m";
            case 'o': return "\033[32m";
            case '=': return "\033[33m";
            case '*': return "\033[34m";
            case '%': return "\033[35m";
            case '$': return "\033[36m";
            default: return "\033[0m";
        }
    }
}

CLIpc::CLIpc(bool colorIsSet) :
    colorIsSet_(colorIsSet)
{
}

CLIpc::~CLIpc()
{
    std::cout << "\033[0m\033[?25h" << std::flush;
}

void CLIpc::drawPixel(std::size_t x, std::size_t y, char pixel)
{
    if (x >= DisplayWidth || y >= DisplayHeight)
    {
        return;
    }
    std::cout << "\033[" << y + 1 << ';' << x + 1 << 'H';
    if (colorIsSet_)
    {
        std::cout << colorFor(pixel);
    }
    std::cout << pixel << "\033[0m" << std::flush;
}

void CLIpc::drawBuffer(const RowView& row)
{
    for (std::size_t x = 0; x < row.size(); ++x)
    {
        const char pixel = row[x];
        if (colorIsSet_ && pixel != ' ')
        {
            std::cout << colorFor(pixel);
        }
        std::cout << pixel;
        if (colorIsSet_ && pixel != ' ')
        {
            std::cout << "\033[0m";
        }
    }
    std::cout << '\n';
}

void CLIpc::clear()
{
    std::cout << "\033[2J\033[H\033[?25l";
}

std::size_t CLIpc::getWidth() const
{
    return DisplayWidth;
}

std::size_t CLIpc::getHeight() const
{
    return DisplayHeight;
}