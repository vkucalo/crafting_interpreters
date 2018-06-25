#pragma once
#include <string>
#include "lox_callable.h"

enum value_type {
    STRING_VALUE, DOUBLE_VALUE, BOOLEAN_VALUE, NILL_VALUE, CALLABLE_VALUE
};

struct value {
    std::string string_value;
    double double_value = 0;
    bool boolean_value;
    lox_callable* callable_value;

    value_type v_type;

    value(std::string s);
    value(double d);
    value(bool b);
    value(lox_callable* c);
    value();
    std::string stringify();
};