//
// Created by viktor on 07.01.18..
//
#pragma once

#include <string>
#include <iostream>

struct error_logger{

    bool had_error;

    void report(int line, std::string where, std::string message){
        std::cout << "[line " << line << " ] Error " << where << ": " << message;
        had_error = true;
    }

    void error(std::string message, int line){
        report(line, "", message);
    }

};
