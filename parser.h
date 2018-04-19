#pragma once
#include "stmt.h"
#include <vector>
#include <iostream>
#include "lox_runtime_error.h"

struct parser {
    
    std::vector<token> tokens;
    int current = 0;

    parser(std::vector<token>& t) : tokens(t) {};

    bool is_at_end(){
        return tokens[current].type == token_type::EOTF;
    }

    token peek(){
        return tokens[current];
    }

    token previous(){
        return tokens[current - 1];
    }

    token advance(){
        if (!is_at_end())
            current++;
        return previous();
    }

    bool check(token_type type){
        return is_at_end() ? false : peek().type == type;
    }

    bool match(std::vector<token_type> types){
        for (auto& type : types){
            if (check(type)){
                advance();
                return true;
            }
        }
        return false;
    }

    // void error(token tok, std::string& message){
    //     if (tok.type == token_type::EOTF)
    //         report(tok.line, " at end", message);
    //     else
    //         report(tok.line, " at"); //TODO
    // }

    token consume(token_type type, std::string message){
        if (check(type))
            return advance();
        std::cout << message;
    }

    expr* primary(){
        if (match({FALSE}))
            return new literal("false");
        if (match({TRUE}))
            return new literal("true");
        if (match({NIL}))
            return new literal("nil");
        if (match({NUMBER}))
            return new literal(std::stod(previous().literal));
        if (match({STRING}))
            return new literal(previous().literal);
        if (match({LEFT_PAREN})){
            expr* expr = expression();
            consume(token_type::RIGHT_PAREN, "Expect ) after expression");
            return new grouping(expr);
        }
        if (match({IDENTIFIER}))
            return new var_expr(previous());

    }

    expr* unar(){
        if(match({BANG, MINUS})){
            token oper = previous();
            expr* right = unar();
            return new unary(right, oper);
        }
        return primary();
    }

    expr* multiplication(){
        expr* expression = unar();
        while(match({SLASH, STAR})){
            token oper = previous();
            expr* right = unar();
            expression = new binary(expression, oper, right);
        }
        return expression;
    }

    expr* addition(){
        expr* expression = multiplication();
        while(match({MINUS, PLUS})){
            token oper = previous();
            expr* right = multiplication();
            expression = new binary(expression, oper, right);
        }
        return expression;
    }

    expr* comparison(){
        expr* expression = addition();
        while(match({LESS, LESS_EQUAL, GREATER, GREATER_EQUAL})){
            token oper = previous();
            expr* right = addition();
            expression = new binary(expression, oper, right);
        }
        return expression;
    }

    expr* equality(){
        expr* expression = comparison();
        while(match({BANG_EQUAL,EQUAL_EQUAL})){
            token oper = previous();
            expr* right = comparison();
            expression = new binary(expression, oper, right);
        }
        return expression;
    }

    expr* assignment(){
        expr* left = equality();

        if (match({EQUAL})){
            expr* right = assignment();
            var_expr* asignee = dynamic_cast<var_expr*>(left);
            if (asignee)
                return new assignment_expr(right, asignee->tok);
            std::cout << "Invalid assignment target.";
        }
        return left;
    }

    expr* expression(){
        return assignment();
    }

    // expr* ternary_exp(){
    //     expr* exprs = expression();
    //     while(match({QMARK})){
    //         expr* thenn = expression();
    //         consume(COLON, "expected a : ");
    //         expr* elsee = expression();
    //         exprs = new ternary(exprs, thenn, elsee);
    //     }
    //     return exprs;
    // }

    void synchronize() {
        advance();

        while (!is_at_end()) {
            if (previous().type == token_type::SEMICOLON) return;

            switch (peek().type) {
                case CLASS:
                case FUN:
                case VAR:
                case FOR:
                case IF:
                case WHILE:
                case PRINT:
                case RETURN:
                return;
            }

            advance();
        }
    }

    expr_stmt* expression_statement(){
        expr* ex = expression();
        consume(SEMICOLON, "Expected ; after statement.");
        return new expr_stmt(ex);
    }

    print_stmt* print_statement(){
        expr* ex = expression();
        consume(SEMICOLON, "Expected ; after statement.");
        return new print_stmt(ex);
    }

    block_stmt* block_statement(){
        std::vector<stmt*> statements;
        while(!check({RIGHT_BRACE}) && !is_at_end()){
            statements.emplace_back(declaration());
        }
        consume(RIGHT_BRACE, "Expected a } after block.");
        return new block_stmt(statements);
    }

    stmt* statement(){
        if (match({PRINT}))
            return print_statement();
        if (match({LEFT_BRACE}))
            return block_statement();
        return expression_statement();
    }

    stmt* var_declaration(){
        token name = consume(IDENTIFIER, "Expected a variable name");
        expr_stmt* e = nullptr;
        if (match({EQUAL})) 
            e = expression_statement();
        return new var_stmt(e->expression, name);
    }

    stmt* declaration(){
        if(match({VAR}))
            return var_declaration();
        return statement();
    }

    std::vector<stmt*> parse(){
        std::vector<stmt*> statements;
        while(!is_at_end())
            statements.emplace_back(declaration());
        return statements;
    }
};