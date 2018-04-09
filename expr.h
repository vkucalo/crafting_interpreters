#pragma once
#include <string>
#include "token.h"


struct binary;
struct grouping;
struct unary;
struct literal;
struct ternary;

struct expr_visitor{
    virtual std::string visit(binary* expr) = 0;
    virtual std::string visit(grouping* expr) = 0;
    virtual std::string visit(unary* expr) = 0;
    virtual std::string visit(literal* expr) = 0;
    virtual std::string visit(ternary* expr) = 0;
};

struct expr {
    virtual std::string accept(expr_visitor* visitor) = 0; 
};

struct grouping : expr {
    expr* expression;

    grouping(expr* e) : expression(e) {};

    std::string accept(expr_visitor* visitor){
        return visitor->visit(this);
    }
};

struct binary : expr {
    expr* left;
    token op;
    expr* right;

    binary(expr* l, token tok, expr* r) : left(l), op(tok), right(r) {};

    std::string accept(expr_visitor* visitor){
        return visitor->visit(this);
    }
};

struct unary : expr {
    expr* ex;
    token op;

    unary(expr* e, token t) : ex(e), op(t) {};

    std::string accept(expr_visitor* visitor){
        return visitor->visit(this);
    }
};

struct ternary : expr {
    expr* ex;
    expr* then_branch;
    expr* else_branch;

    ternary(expr* e, expr* t_b, expr* e_b) : ex(e), then_branch(t_b), else_branch(e_b) {}

    std::string accept(expr_visitor* visitor){
        visitor->visit(this);
    }
};

struct literal : expr{ 
	std::string value;

	literal(std::string val) : value(val) {};

    std::string accept(expr_visitor* visitor){
        return visitor->visit(this);
    }
};


