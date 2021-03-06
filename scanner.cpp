#include "scanner.h"

void scanner::init_keywords(){
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

bool scanner::has_next(){
    return current < source.size();
}

bool scanner::is_digit(char c){
    return std::isdigit(c);
}

void scanner::add_token(token_type type){
    add_token(type, "");
}

void scanner::add_token(token_type type, const std::string& literal){
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}

char scanner::advance(){
    current++;
    return source[current - 1];
}

bool scanner::match(char expected){
    if (!has_next()) return false;
    if (source[current] != expected) return false;
    current++;
    return true;
}

char scanner::peek(){
    if (!has_next()) return '\0';
    return source[current];
}

char scanner::peek_next(){
    if (current + 1 >= source.size()) return '\0';
    return source[current + 1];
}

void scanner::number(){

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

void scanner::identifier(){
    while(isalnum(peek())){
        advance();
    } 
    std::string text = source.substr(start, current - start);
    auto type = keywords.find(text);
    type == keywords.end() ? add_token(IDENTIFIER) : add_token(type->second);
}

void scanner::string(){

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

    std::string value = source.substr(start + 1, current - start - 2);
    add_token(STRING, value);
}

void scanner::scan_token(){
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

scanner::scanner (const std::string& s, error_logger e) : source(s){
    logger = e;
    init_keywords();
}

std::vector<token> scanner::scan_tokens(){
    while(has_next()){
        start = current;
        scan_token();
    }
    tokens.emplace_back(EOTF, "","", line);
    return tokens;
}
