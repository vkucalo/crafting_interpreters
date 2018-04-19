#pragma once
#include "expr.h"

struct expr_stmt;
struct print_stmt;
struct block_stmt;
struct var_stmt;

struct stmt_visitor {
    virtual void visit(expr_stmt*) = 0;
    virtual void visit(print_stmt*) = 0;
    virtual void visit(var_stmt* v) = 0;
    virtual void visit(block_stmt* v) = 0;
    // virtual void visit(block_stmt* v) = 0;
};

struct stmt {
    virtual void accept(stmt_visitor* visitor) = 0;
};

struct expr_stmt : stmt { 
    expr* expression;
    
    expr_stmt(expr* ex) : expression(ex) {};

    void accept(stmt_visitor* visitor){
        visitor->visit(this);
    }
};
 
struct print_stmt : stmt {
    expr* expression;
    
    print_stmt(expr* ex) : expression(ex) {};

    void accept(stmt_visitor* visitor){
        visitor->visit(this);
    }
};

struct var_stmt : stmt {
    expr* expression;
    token name;

    var_stmt(expr* e, token t) : expression(e), name(t) {};

    void accept(stmt_visitor* visitor){
        visitor->visit(this);
    }
};

struct block_stmt : stmt {
    std::vector<stmt*> statements;

    block_stmt(std::vector<stmt*> s) : statements(s) {};

    void accept(stmt_visitor* visitor){
        visitor->visit(this);
    }
};