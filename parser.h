#pragma once
#include "expr.h"
#include <vector>
#include <iostream>

struct parser {
    
    std::vector<token> tokens;
    int current = 0;

    parser(std::vector<token>& t) : tokens(t) {}

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

    bool match(std::vector<token_type>& types){
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
        std::cout << "error!";
    }

    expr* primary(){
        if (check(token_type::FALSE))
            return &literal("false");
        if (check(token_type::TRUE))
            return &literal("true");
        if (check(token_type::NIL))
            return &literal("nil");
        if (check(token_type::NUMBER) || check(token_type::STRING))
            return &literal(previous().literal);

        if (check(token_type::LEFT_PAREN)){
            expr* expr = expression();
            consume(token_type::RIGHT_PAREN, "Expect ) after expression");
            return &grouping(expr);
        }
    }

    expr* unar(){
        std::vector<token_type> eq {token_type::BANG, token_type::MINUS};
        if(match(eq)){
            token oper = previous();
            expr* right = unar();
            return &unary(right, oper);
        }
        return primary();
    }

    expr* multiplication(){
        expr* expression = unar();
        std::vector<token_type> eq {token_type::SLASH, token_type::STAR};
        while(match(eq)){
            token oper = previous();
            expr* right = unar();
            expression = &binary(expression, oper, right);
        }
        return expression;
    }

    expr* addition(){
        expr* expression = multiplication();
        std::vector<token_type> eq {token_type::MINUS, token_type::PLUS};
        while(match(eq)){
            token oper = previous();
            expr* right = multiplication();
            expression = &binary(expression, oper, right);
        }
        return expression;
    }

    expr* comparison(){
        expr* expression = addition();
        std::vector<token_type> eq {token_type::LESS, token_type::LESS_EQUAL, token_type::GREATER, token_type::GREATER_EQUAL};
        while(match(eq)){
            token oper = previous();
            expr* right = addition();
            expression = &binary(expression, oper, right);
        }
        return expression;
    }

    expr* equality(){
        expr* expression = comparison();
        std::vector<token_type> eq {token_type::BANG_EQUAL, token_type::EQUAL_EQUAL};
        while(match(eq)){
            token oper = previous();
            expr* right = comparison();
            expression = &binary(expression, oper, right);
        }
        return expression;
    }

    expr* expression(){
        return equality();
    }

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

    expr* parse(){
        return expression();
    }

};