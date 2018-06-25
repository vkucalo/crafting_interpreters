#include "token.h"

token::token() { };

token::token(const token_type type, const std::string &lexeme,
        const std::string &literal, int line) : type(type), lexeme(lexeme),
                                                    literal(literal), line(line) { }
std::string token::str(){
    return std::string(lexeme + " " + literal);
}