/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/Core/ConsoleLog.hpp>

#include <iostream>

namespace zt {
    
    void ConsoleLog::log(Log::Type type, const std::string& message) {
        if (type == Type::INFO) {
            std::cout << "INFO:\t" << message << std::endl;
        }
        else if (type == Type::SUCCESS) {
            std::cout << "\033[32mSUCCESS:\t" << message << std::endl;
        }
        else if (type == Type::WARNING) {
            std::cout << "\033[33mWARNING:\t" << message << std::endl;
        }
        else if (type == Type::ERROR) {
            std::cout << "\033[31mERROR:\t" << message << std::endl;
        }
        std::cout << "\033[0m";
    }
    
}