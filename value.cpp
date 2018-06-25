#include "value.h"

value::value(std::string s) : string_value(s), v_type(STRING_VALUE) {};

value::value(double d) : double_value(d), v_type(DOUBLE_VALUE) {};

value::value(bool b) : boolean_value(b), v_type(BOOLEAN_VALUE) {};

value::value(lox_callable* c) : callable_value(c), v_type(CALLABLE_VALUE) {};

value::value() : v_type(NILL_VALUE) {};

std::string value::stringify(){
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
