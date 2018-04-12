#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "token.h"
#include "error_logger.h"

class scanner {

    std::string source;
    std::vector<token> tokens;
    error_logger logger;
    std::map<std::string, token_type> keywords;
    int start = 0;
    int current = 0;
    int line = 1;

    void init_keywords(){
        keywords["and"]    = AND;
        keywords["class"]  = CLASS;
        keywords["class"]  = CLASS;
        keywords["else"]   = ELSE;
        keywords["false"]  = FALSE;
        keywords["for"]    = FOR;
        keywords["fun"]    = FUN;
        keywords["if"]     = IF;
        keywords["nil"]    = NIL;
        keywords["or"]     = OR;
        keywords["print"]  = PRINT;
        keywords["return"] = RETURN;
        keywords["super"]  = SUPER;
        keywords["this"]   = THIS;
        keywords["true"]   = TRUE;
        keywords["var"]    = VAR;
        keywords["while"]  = WHILE;
    }

    bool has_next(){
        return current < source.size();
    }

    bool is_digit(char c){
        return std::isdigit(c);
    }

    void add_token(token_type type){
        add_token(type, "");
    }

    void add_token(token_type type, const std::string& literal){
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
    }

    char advance(){
        current++;
        return source[current - 1];
    }

    bool match(char expected){
        if (!has_next()) return false;
        if (source[current] != expected) return false;
        current++;
        return true;
    }

    char peek(){
        if (!has_next()) return '\0';
        return source[current];
    }

    char peek_next(){
        if (current + 1 >= source.size()) return '\0';
        return source[current + 1];
    }

    void number(){

        while (is_digit(peek())){
            advance();
        } 

        if (peek() == '.' && is_digit(peek_next())){
            advance();
            while (is_digit(peek())){
                advance();
            } 
        }

        add_token(NUMBER, source.substr(start, current - start));
    }

    void identifier(){
        while(isalnum(peek())){
            advance();
        } 
        add_token(IDENTIFIER);
    }

    void string(){
        while (peek() != '"' && has_next()){
            if (peek() == '\n') line++;
            advance();
        }

        //Unterminated string
        if (!has_next()){
            logger.error("Unterminated string", line);
            return;
        }

        advance();

        std::string value = source.substr(start + 1, current - start - 1);
        add_token(STRING, value);
    }

    void scan_token(){
        char c = advance();
        switch(c){
            case '(': add_token(LEFT_PAREN); break;
            case ')': add_token(RIGHT_PAREN); break;
            case '{': add_token(LEFT_BRACE); break;
            case '}': add_token(RIGHT_BRACE); break;
            case ',': add_token(COMMA); break;
            case '.': add_token(DOT); break;
            case '-': add_token(MINUS); break;
            case '+': add_token(PLUS); break;
            case ';': add_token(SEMICOLON); break;
            case '*': add_token(STAR); break;
            case '?': add_token(QMARK); break;
            case ':': add_token(COLON); break;
            case '!': add_token(match('=') ? BANG_EQUAL : BANG); break;
            case '=': add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
            case '<': add_token(match('=') ? LESS_EQUAL : LESS); break;
            case '>': add_token(match('=') ? GREATER_EQUAL : GREATER); break;
            case '/':
                if (match('/'))
                    while (peek () != '\n' && !has_next()) advance();
                else
                    add_token(SLASH);
                break;
            case ' ':
            case '\r':
            case '\t': break;
            case '\n': line++; break;
            case '"': string(); break;

            default:
                if (is_digit(c))
                    number();
                else if (isalpha(c))
                    identifier();
                else
                    std::cout << "Unexpected character, line = ", line; break;

        }
    }

public:

    scanner (const std::string& s, error_logger e) : source(s){
        logger = e;
        init_keywords();
    }

    std::vector<token> scan_tokens(){
        while(has_next()){
            start = current;
            scan_token();
        }
        tokens.emplace_back(EOTF, "","", line);
        return tokens;
    }


};
