#pragma once

struct binary;
struct grouping;
struct unary;
struct literal;
struct ternary;
struct var_expr;
struct assignment_expr;
struct logical_expr;
struct call_expr; 

struct expr_visitor{
    virtual void visit(binary* expr) = 0;
    virtual void visit(grouping* expr) = 0;
    virtual void visit(unary* expr) = 0;
    virtual void visit(literal* expr) = 0;
    virtual void visit(var_expr* expr) = 0;
    virtual void visit(assignment_expr* expr) = 0;
    virtual void visit(logical_expr* expr) = 0;
    virtual void visit(call_expr* expr) = 0;
};
