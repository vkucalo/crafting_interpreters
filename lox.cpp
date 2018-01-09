#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "scanner.h"


using namespace std;


static void run(const string& source) {
    error_logger log;
    scanner scanner(source, log);
    vector<token> tokens = scanner.scan_tokens();

    for(auto& token : tokens) {
        cout << token.str() << endl;
    }
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

//int main(){
//    run("hej x = lol if ( 4 < 32.323) ");
//    return 0;
//}