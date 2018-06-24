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
    lox_callable callable_value;

    value_type v_type;

    value(std::string s) : string_value(s), v_type(STRING_VALUE) {};

    value(double d) : double_value(d), v_type(DOUBLE_VALUE) {};

    value(bool b) : boolean_value(b), v_type(BOOLEAN_VALUE) {};

    value(lox_callable c) : callable_value(c), v_type(CALLABLE_VALUE) {};
    
    value() : v_type(NILL_VALUE) {};

    std::string stringify(){
        switch(v_type){
            case STRING_VALUE: return string_value;
            case DOUBLE_VALUE: 
                if (int(double_value) == double_value)
                    return std::to_string(int(double_value));
                return std::to_string(double_value);
            case BOOLEAN_VALUE: return std::to_string(boolean_value);
            case NILL_VALUE: return "nill";
        }
    }
};