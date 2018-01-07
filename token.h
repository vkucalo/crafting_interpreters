//
// Created by viktor on 06.01.18..
//

#ifndef CRAFTINGINTERPRETERS_TOKEN_H
#define CRAFTINGINTERPRETERS_TOKEN_H

#include <string>

enum token_type {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens
            BANG, BANG_EQUAL,
            EQUAL, EQUAL_EQUAL,
            GREATER, GREATER_EQUAL,
            LESS, LESS_EQUAL,

    // Literals
            IDENTIFIER, STRING, NUMBER,

    // Keywords
            AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
            PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOTF
};

struct token {
    token_type type;
    std::string lexeme;
    std::string literal;
    int line;

    token(const token_type type, const std::string &lexeme,
          const std::string &literal, int line) : type(type), lexeme(lexeme),
                                                        literal(literal), line(line) { }
    std::string str(){
        return std::string(type + " " + lexeme + " " + literal);
    }



};
#endif //CRAFTINGINTERPRETERS_TOKEN_H
