#pragma once
#include <vector>
#include "interpreter.h"
#include "value.h"

struct lox_callable {
    int arity;
    virtual value call(interpreter inter, std::vector<value> arguments) = 0;
}