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

    void init_keywords();
    bool has_next();
    bool is_digit(char c);
    void add_token(token_type type);
    void add_token(token_type type, const std::string& literal);
    char advance();
    bool match(char expected);
    char peek();
    char peek_next();
    void number();
    void identifier();
    void string();
    void scan_token();
public:
    scanner (const std::string& s, error_logger e);
    std::vector<token> scan_tokens();
};
