#pragma once
#include <string>
#include "token.h"
#include "value.h"
#include "expr_visitor.h"

struct expr {
    virtual void accept(expr_visitor* visitor) = 0; 
};

struct grouping : expr {
    expr* expression;

    grouping(expr* e);
    void accept(expr_visitor* visitor);
};

struct binary : expr {
    expr* left;
    token op;
    expr* right;

    binary(expr* l, token tok, expr* r);
    void accept(expr_visitor* visitor);
};

struct unary : expr {
    expr* ex;
    token op;

    unary(expr* e, token t);
    void accept(expr_visitor* visitor);
};

struct literal : expr { 
	value val;
	literal(std::string v);
    literal(double d);
    literal(bool b);
    literal();
    void accept(expr_visitor* visitor);
};

struct var_expr : expr {
    token tok;

    var_expr(token t);
    void accept(expr_visitor* visitor);
};

struct assignment_expr : expr {
    token left;
    expr* ex;

    assignment_expr(expr* e, token l);
    void accept(expr_visitor* visitor);
};

struct logical_expr : expr {
    expr* left;
    token oper;
    expr* right;

    logical_expr(expr* l, token t, expr* r);
    void accept(expr_visitor* visitor);
};

struct call_expr : expr {
    expr* callee;
    token paren;
    std::vector<expr*> arguments;

    call_expr(expr* c, token par, std::vector<expr*>& args);

    void accept(expr_visitor* visitor);
};

