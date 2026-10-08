#include "InputParser.h"

#include <cerrno>
#include <iostream>
#include <string>
#include <system_error>

#include <sys/select.h>
#include <unistd.h>

namespace InputParser
{
    bool exit_program()
    {
        fd_set input;
        FD_ZERO(&input);
        FD_SET(STDIN_FILENO, &input);

        timeval timeout{};
        const int result = select(STDIN_FILENO + 1, &input, nullptr, nullptr, &timeout);
        if (result < 0)
        {
            if (errno == EINTR)
            {
                return false;
            }
            throw std::system_error(errno, std::generic_category(), "select stdin");
        }
        if (result == 0)
        {
            return false;
        }

        std::string command;
        if (!std::getline(std::cin, command))
        {
            return true;
        }
        return command == "q" || command == "clear";
    }
}