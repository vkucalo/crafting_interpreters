#pragma once
#include <vector>

struct interpreter;
struct value;

struct lox_callable {
    virtual int arity() = 0;
    virtual value call(interpreter* inter, std::vector<value> arguments) = 0;
};