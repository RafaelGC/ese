/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/Core/Log.hpp>

namespace zt {
    void Log::error(const std::string& message) {
        log(Type::ERROR, message);
    }
    
    void Log::info(const std::string& message) {
        log(Type::INFO, message);
    }
    
    void Log::warning(const std::string& message) {
        log(Type::WARNING, message);
    }
    
    void Log::success(const std::string& message) {
        log(Type::SUCCESS, message);
    }
}