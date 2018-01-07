//
// Created by viktor on 07.01.18..
//

#ifndef CRAFTINGINTERPRETERS_ERROR_LOGGER_H
#define CRAFTINGINTERPRETERS_ERROR_LOGGER_H

#include <string>
#include <iostream>

struct error_logger{

    static bool had_error;

    static void report(int line, std::string where, std::string message){
        std::cout << "[line ", line, " ] Error ", where, ": ", message;
        had_error = true;
    }

    static void error(std::string message, int line){
        report(line, "", message);
    }

};

#endif //CRAFTINGINTERPRETERS_ERROR_LOGGER_H
