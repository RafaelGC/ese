/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Log.hpp
 * Author: rafa
 *
 * Created on February 9, 2018, 8:35 PM
 */

#ifndef ZELTALIB_LOG_HPP
#define ZELTALIB_LOG_HPP

#include <string>

#ifdef ZELTALIB_DEBUG
#define ZELTALIB_LOG_WARNING(LOG, MESSAGE) LOG.log(zt::Log::Type::WARNING, MESSAGE);
#define ZELTALIB_LOG_INFO(LOG, MESSAGE) LOG.log(zt::Log::Type::INFO, MESSAGE);
#define ZELTALIB_LOG_ERROR(LOG, MESSAGE) LOG.log(zt::Log::Type::ERROR, MESSAGE);
#define ZELTALIB_LOG_SUCCESS(LOG, MESSAGE) LOG.log(zt::Log::Type::SUCCESS, MESSAGE);
#else
#define ZELTALIB_LOG_WARNING(LOG, MESSAGE)
#define ZELTALIB_LOG_INFO(LOG, MESSAGE)
#define ZELTALIB_LOG_ERROR(LOG, MESSAGE)
#define ZELTALIB_LOG_SUCCESS(LOG, MESSAGE)
#endif

namespace zt {
    /**
     * @brief Base class for logging.
     * 
     * You may find useful the ZELTA_LOG_WARNING(...), ZELTA_LOG_INFO(...),
     * ZELTA_LOG_ERROR(...) and ZELTA_LOG_SUCCESS(...) directives that
     * only logs when the ZELTALIB_DEBUG directive si defined.
     */
    class Log {
    public:
        enum class Type {
            ERROR, WARNING, INFO, SUCCESS
        };
        
        Log() {
            lastMode = Type::INFO;
        }
        
        virtual void log(Log::Type type, const std::string& message) = 0;
        
        virtual void error(const std::string& message);
        virtual void info(const std::string& message);
        virtual void warning(const std::string& message);
        virtual void success(const std::string& message);
        
    protected:
        Type lastMode;
    };
}
#endif /* LOG_HPP */

