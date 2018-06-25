#include "lox_function.h"

lox_function::lox_function(fun_stmt* d) : declaration(d) {}

int lox_function::arity(){
    return declaration->parameters.size();
}

value lox_function::call(interpreter* inter, std::vector<value> arguments){
    environment env = new environment(inter->env);
    for (int i = 0; i < declaration->parameters.size(); ++i){
        env.define(declaration->parameters[i].lexeme, arguments[i]);
    }
    inter->execute_block(declaration->body, env);
    return inter->result;
}