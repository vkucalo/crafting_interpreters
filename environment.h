#pragma once
#include <unordered_map>
#include <string>
#include "value.h"
#include "token.h"
#include "lox_runtime_error.h"

struct environment {
    environment* enclosing;
    std::unordered_map<std::string, value> values;

    environment();
    environment(environment* e);
    void define(std::string name, value val);
    value get(token name);
    void assign(token name, value val);
};