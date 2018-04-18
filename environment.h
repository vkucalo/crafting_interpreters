#pragma once
#include <unordered_map>
#include <string>
#include "value.h"
#include "token.h"
#include "lox_runtime_error.h"

struct environment {
    std::unordered_map<std::string, value> values;

    void define(std::string name, value val){
        values[name] = val;
    }

    value get(token name){ 
        auto ret = values.find(name.lexeme);
        if (ret != values.end())
            return ret->second;
        throw new lox_runtime_error(name, std::string("Undefined variable " + name.lexeme + "."));
    }

    void assign(token name, value val){
        auto ret = values.find(name.lexeme);
        if (ret != values.end())
            values[name.lexeme] = val;
        else
            throw new lox_runtime_error(name, std::string("Undefined variable " + name.lexeme + "."));
    }
};