#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <Zelta/Core/Log.hpp>

namespace zt {

    /**
     * @brief Class for logging to a file.
     */
    class FileLog : public Log {
    public:

        enum class Mode {
            KEEP_PREVIOUS_LOG, REMOVE_PREVIOUS_LOG
        };
        
        /**
         * Constructs a FileLog. You should open the file before logging using
         * the open() method or using the second constructor instead.
         */
        FileLog();
        
        /**
         * @param filename Output file.
         * @param mode If the file already exists you can either keep it or override it.
         */
        FileLog(const std::string& filename, Mode mode = Mode::KEEP_PREVIOUS_LOG);
        ~FileLog();
        
        /**
         * @brief Open the log file.
         * @param Filename.
         * @param MODE If the file already exists you can keep it or you can override it.
         * @return TRUE si el archivo está abierto y se puede escribir, si no, FALSE.
         * */
        bool open(const std::string& filename, Mode mode = Mode::KEEP_PREVIOUS_LOG);

        /**
         * @brief Closes the log file. You won't be able to write after closing it.
         * If you don't call it explicitly it will be called in the destructor.
         * */
        void close();
        
        void log(Log::Type type, const std::string& message);
        
        FileLog& operator <<(const std::string& message);
        FileLog& operator <<(const Log::Type& type);

    private:
        std::ofstream outputFile;
        bool mOpen;
    };

}
#endif // LOG_HPP
