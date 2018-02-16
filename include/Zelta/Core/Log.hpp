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
/*Con las definiciones anteriores se consigue optimizar el programa. Si el usuario establece el
 * modo de depuración definiendo la constante ZELTALIB_DEBUG y hace uso de algunos de esos
 * métodos, efectivamente, llamará a los métodos correspondientes. Sin embargo, si no
 * está definida la constante ZELTALIB_DEBUG, las llamadas a los métodos LOG_XXX serán
 * ignoradas. La ventaja de esto es que se hace al momento de compilar y no en tiempo
 * de ejecución.
 */

namespace zt {
    /**
     * Base class for logging.
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

