#ifndef PARSER_HPP
#define PARSER_HPP

#include "Core.hpp"
#include <libconfig.h++>

class Parser {
public:
    Parser() = default;
    ~Parser() = default;

    static int parsing(int argc, char *argv[], Core *core);
};

#endif