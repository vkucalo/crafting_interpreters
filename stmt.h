#pragma once
#include "expr.h"

struct expr_stmt;
struct print_stmt;

struct stmt_visitor {
    virtual void visit(expr_stmt*) = 0;
    virtual void visit(print_stmt*) = 0;
};

struct stmt {
    virtual void accept(stmt_visitor* visitor) = 0;
};

struct expr_stmt : stmt { 
    expr* expression;
    
    expr_stmt(expr* ex) : expression(ex) {}

    void accept(stmt_visitor* visitor){
        visitor->visit(this);
    }
};
 
struct print_stmt : stmt {
    expr* expression;
    
    print_stmt(expr* ex) : expression(ex) {}

    void accept(stmt_visitor* visitor){
        visitor->visit(this);
    }
};