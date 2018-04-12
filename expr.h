#pragma once
#include <string>
#include "token.h"
#include "value.h"

struct binary;
struct grouping;
struct unary;
struct literal;
struct ternary;

struct expr_visitor{
    virtual void visit(binary* expr) = 0;
    virtual void visit(grouping* expr) = 0;
    virtual void visit(unary* expr) = 0;
    virtual void visit(literal* expr) = 0;
    // virtual void visit(ternary* expr) = 0;
};

struct expr {
    virtual void accept(expr_visitor* visitor) = 0; 
};

struct grouping : expr {
    expr* expression;

    grouping(expr* e) : expression(e) {};

    void accept(expr_visitor* visitor){
        visitor->visit(this);
    }
};

struct binary : expr {
    expr* left;
    token op;
    expr* right;

    binary(expr* l, token tok, expr* r) : left(l), op(tok), right(r) {};

    void accept(expr_visitor* visitor){
        visitor->visit(this);
    }
};

struct unary : expr {
    expr* ex;
    token op;

    unary(expr* e, token t) : ex(e), op(t) {};

    void accept(expr_visitor* visitor){
        visitor->visit(this);
    }
};

// struct ternary : expr {
//     expr* ex;
//     expr* then_branch;
//     expr* else_branch;

//     ternary(expr* e, expr* t_b, expr* e_b) : ex(e), then_branch(t_b), else_branch(e_b) {}

//     void accept(expr_visitor* visitor){
//         visitor->visit(this);
//     }
// };

struct literal : expr{ 
	value val;

	literal(std::string v) : val(v) {};

    literal(double d) : val(d) {};

    literal(bool b) : val(b) {};

    literal() : val() {};

    void accept(expr_visitor* visitor){
        visitor->visit(this);
    }
};


