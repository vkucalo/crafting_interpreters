#pragma once
#include "expr.h"
#include "stmt_visitor.h"
#include <vector>

struct expr;
struct stmt_visitor;

struct stmt {
    virtual void accept(stmt_visitor* visitor) = 0;
};

struct expr_stmt : stmt { 
    expr* expression;
    
    expr_stmt(expr* ex);
    void accept(stmt_visitor* visitor);
};
 
struct print_stmt : stmt {
    expr* expression;
    
    print_stmt(expr* ex);
    void accept(stmt_visitor* visitor);
};

struct var_stmt : stmt {
    expr* expression;
    token name;

    var_stmt(expr* e, token t);
    void accept(stmt_visitor* visitor);
};

struct block_stmt : stmt {
    std::vector<stmt*> statements;

    block_stmt(std::vector<stmt*> s);
    void accept(stmt_visitor* visitor);
};

struct if_stmt : stmt {
    expr* condition;
    stmt* then_branch;
    stmt* else_branch;

    if_stmt(expr* c, stmt* t, stmt* e);
    void accept(stmt_visitor* visitor);
};

struct while_stmt : stmt {
    expr* condition;
    stmt* statement;

    while_stmt(expr* c, stmt* s);
    void accept(stmt_visitor* visitor);
};

struct fun_stmt : stmt {
    token name;
    std::vector<token> parameters;
    block_stmt* body;

    fun_stmt(token n, std::vector<token> p, block_stmt* b);

    void accept(stmt_visitor* visitor);
};