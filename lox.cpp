#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "scanner.h"
#include "ast_printer.h"
#include "parser.h"


using namespace std;

static void run(const string& source) {
    error_logger log;
    scanner scanner(source, log);
    vector<token> tokens = scanner.scan_tokens();
    parser p(tokens);
    expr* expr = p.parse();

    ast_printer printer(expr);
    std::cout << printer.print();
}

static void run_file(char* path){
    ifstream file_contents(path);
    stringstream file_as_sstream;
    file_as_sstream << file_contents.rdbuf();
}

static void run_prompt(){
    error_logger log;
    for(;;){
        cout << ">";
        string s;
        cin >> s;
        run(s);
        if (log.had_error) return;
    }
}

bool error_logger::had_error = false;

int main(int argc, char** argv){
    std::string argument = argv[1];
    if (argc < 2)
        std::cout << "Invalid argument \t -s for source and -i for interactive" << std::endl;
    if (argument == "-i")
        run_prompt();
    if (argument == "-s")
        run(argv[2]);
    return 0;
}