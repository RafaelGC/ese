#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <Zelta/Core/Log.hpp>

namespace zt {

    class FileLog : public Log {
    public:

        enum class Mode {
            KEEP_PREVIOUS_LOG, REMOVE_PREVIOUS_LOG
        };
        
        FileLog();
        FileLog(const std::string& filename, Mode mode = Mode::KEEP_PREVIOUS_LOG);
        ~FileLog();
        
        /**
         * @brief Abre el archivo de log para ser escrito.
         * @param Nombre del fichero de salida.
         * @param MODE Modo de apertura. Si es KEEP_PREVIOUS_LOG no se perderá
         * el log anterior. Si es REMOVE_PREVIOUS_LOG se sobreescribirá.
         * @return TRUE si el archivo está abierto y se puede escribir, si no, FALSE.
         * */
        bool open(const std::string& filename, Mode mode = Mode::KEEP_PREVIOUS_LOG);

        /**
         * @brief Cierra el archivo, no se podrá escribir en él después de liberarlo.
         * El archivo, si no se ha cerrado, se cierra automáticamente desde el
         * destructor.
         * */
        void close();
        
        void log(Log::Type type, const std::string& message);

    private:
        std::ofstream outputFile;
        bool mOpen;
    };

}
#endif // LOG_HPP
