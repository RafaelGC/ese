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
            std::cout << message << std::endl;
        }
        else if (type == Type::SUCCESS) {
            std::cout << "\033[32m" << message << std::endl;
        }
        else if (type == Type::WARNING) {
            std::cout << "\033[33m" << message << std::endl;
        }
        else if (type == Type::ERROR) {
            std::cout << "\033[31m" << message << std::endl;
        }
        std::cout << "\033[0m";
    }
    
    ConsoleLog& ConsoleLog::operator <<(const std::string& message) {
        log(lastMode, message);
        return *this;
    }
    
    ConsoleLog& ConsoleLog::operator <<(const Log<ConsoleLog>::Type& type) {
        lastMode = type;
        return *this;
    }
}