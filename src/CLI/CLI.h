#pragma once

#include "Shape.h"

class CLICommands
{
    public:
        static void moveCursor(int x, int y);
        static void clearScreen();
        static void hideCursor();
        static void showCursor();
        static int getScreenWidth();
        static int getScreenHeight();

    private:
        CLICommands() = default;
};

class CLIBuffer
{
    public:
        CLIBuffer(int width, int height, bool isColorSet);
        ~CLIBuffer();
        void clearBuffer();
        void printShape(const Shape* shape);

    private:
        CLIBuffer(const CLIBuffer&) = delete;
        CLIBuffer& operator=(const CLIBuffer&) = delete;
        char** _buffer;
        bool _isColorSet;
};