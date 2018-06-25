#pragma once
#include <vector>
#include <iostream>
#include "stmt.h"
#include "lox_runtime_error.h"

struct parser {
    std::vector<token> tokens;
    int current = 0;

    parser(std::vector<token>& t);
    bool is_at_end();
    token peek();
    token previous();
    token advance();
    bool check(token_type type);
    bool match(std::vector<token_type> types);
    // void error(token tok, std::string& message);
    token consume(token_type type, std::string message);
    expr* primary();
    expr* finish_call(expr* callee);
    expr* call();
    expr* unar();
    expr* multiplication();
    expr* addition();
    expr* comparison();
    expr* equality();
    expr* _and();
    expr*_or();
    expr* assignment();
    expr* expression();
    void synchronize();
    expr_stmt* expression_statement();
    print_stmt* print_statement();
    if_stmt* if_statement();
    block_stmt* block_statement();
    stmt* for_statement();
    while_stmt* while_statement();
    stmt* statement();
    stmt* var_declaration();
    stmt* function(std::string kind);
    stmt* declaration();
    std::vector<stmt*> parse();
};