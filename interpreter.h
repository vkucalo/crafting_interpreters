#pragma once
#include <iostream>
#include "expr.h"
#include "value.h"
#include "lox_runtime_error.h"
#include "stmt.h"
#include "environment.h"
#include "lox_callable.h"
#include "lox_function.h"

struct interpreter : expr_visitor, stmt_visitor {
    static environment env;
    value result;
    
    interpreter();
    
    value evaluate_var_expr(var_expr* v);
    value evaluate(expr* expression);
    void check_number_operand(token oper, value operand);
    void check_number_operands(token oper, value left, value right);
    bool is_truthy(value val);
    bool is_equal(value left, value right);
    void visit(binary* expr);
    void visit(grouping* expr);
    void visit(unary* expr);
    void visit(literal* expr);
    void visit(call_expr* expr);
    void visit(var_expr* ex) ;
    void visit(assignment_expr* ex);
    void visit(logical_expr* ex);
    void execute(stmt* statement);
    void execute_block(block_stmt* b, environment inner_env);
    void visit(expr_stmt* ex_stmt);
    void visit(print_stmt* pr_stmt);
    void visit(var_stmt* v);
    void visit(block_stmt* b);
    void visit(if_stmt* s);
    void visit(while_stmt* s);
    void visit(fun_stmt* stmt);
    value interpret(std::vector<stmt*>& statements);
};