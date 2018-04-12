#pragma once
#include <string>

enum value_type {
    STRING_VALUE, DOUBLE_VALUE, BOOLEAN_VALUE, NILL_VALUE
};

struct value {
    std::string string_value;
    double double_value = 0;
    bool boolean_value;

    value_type v_type;

    value(std::string s) : string_value(s), v_type(STRING_VALUE) {};

    value(double d) : double_value(d), v_type(DOUBLE_VALUE) {};

    value(bool b) : boolean_value(b), v_type(BOOLEAN_VALUE) {};

    value() : v_type(NILL_VALUE) {};

    std::string stringify(){
        switch(v_type){
            case STRING_VALUE: return string_value;
            case DOUBLE_VALUE: return std::to_string(double_value);
            case BOOLEAN_VALUE: return std::to_string(boolean_value);
            case NILL_VALUE: return "nill";
        }
    }
};