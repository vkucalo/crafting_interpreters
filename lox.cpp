#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "scanner.h"
#include "ast_printer.h"
#include "parser.h"
#include "interpreter.h"
#include "stmt.h"

static error_logger log;

static void runtime_error(lox_runtime_error e){
    log.error(e.message, e.tok.line);
    log.had_error = true;
}

static void run(const std::string& source) {
    
    scanner scanner(source, log);
    std::vector<token> tokens = scanner.scan_tokens();
    parser p(tokens);
    std::vector<stmt*> statements = p.parse();
    interpreter inter;
    inter.interpret(statements);
    // ast_printer asp(expr);
    // std::cout << asp.print() << std::endl;
    // try {
    //     inter.interpret();
    // }
    // catch (lox_runtime_error e){
    //     std::cout << "caught";
    //     runtime_error(e);
    // }
}

static void run_file(char* path){
    std::ifstream file_contents(path);
    std::stringstream file_as_sstream;
    file_as_sstream << file_contents.rdbuf();
    std::string line;
    while(std::getline(file_as_sstream, line)){
        run(line);       
    }
}

static void run_prompt(){
    for(;;){
        std::cout << ">";
        std::string s;
        std::cin >> s;
        run(s);
        if (log.had_error) return;
    }
}


int main(int argc, char** argv){
    log.had_error = false;
    std::string argument = argv[1];
    if (argc < 2)
        std::cout << "Invalid argument \t -s for source and -i for interactive" << std::endl;
    if (argument == "-i")
        run_prompt();
    if (argument == "-s")
        run_file(argv[2]);
    return 0;
}