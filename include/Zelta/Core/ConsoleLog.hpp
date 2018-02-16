/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConsoleLog.hpp
 * Author: rafa
 *
 * Created on February 9, 2018, 8:57 PM
 */

#ifndef ZELTALIB_CONSOLELOG_HPP
#define ZELTALIB_CONSOLELOG_HPP

#include <Zelta/Core/Log.hpp>

namespace zt {

class ConsoleLog : public Log {
public:
    void log(Log::Type type, const std::string& message);
};

}

#endif /* CONSOLELOG_HPP */
