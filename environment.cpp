#include "environment.h"

environment::environment() {};

environment::environment(environment* e) : enclosing(e) {};

void environment::define(std::string name, value val){
    values[name] = val;
}

value environment::get(token name){ 
    auto ret = values.find(name.lexeme);
    if (ret != values.end())
        return ret->second;
    if (enclosing != nullptr)
        return enclosing->get(name);
    throw new lox_runtime_error(name, std::string("Undefined variable " + name.lexeme + "."));
}

void environment::assign(token name, value val){
    auto ret = values.find(name.lexeme);
    if (ret != values.end()){
        values[name.lexeme] = val;
        return;
    }
    if (enclosing != nullptr){
        enclosing->assign(name, val);
        return;
    }
    throw new lox_runtime_error(name, std::string("Undefined variable " + name.lexeme + "."));
}