#pragma once 
#include "vector"
#include "lox_callable.h"
#include "environment.h"
#include "interpreter.h"

struct fun_stmt;

struct lox_function : lox_callable {
    fun_stmt* declaration;
    lox_function(fun_stmt* d);
    int arity();
    value call(interpreter* inter, std::vector<value> arguments);
};