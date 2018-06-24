#pragma once
#include "token.h"
#include <exception>

struct lox_runtime_error : std::exception {
    const token tok;
    std::string message;

    lox_runtime_error(token t, std::string msg) : tok(t), message(msg) {}
    
    const char * what () const throw () {
        return message.c_str();
    }   
};