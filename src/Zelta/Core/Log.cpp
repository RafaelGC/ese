#include <Zelta/Core/Log.hpp>

std::ofstream zt::Log::outputFile;
//Hay que definir el objeto.

bool zt::Log::open(int mode) {
    if (mode == Log::KEEP_PREVIOUS_LOG) {
        Log::outputFile.open("log.txt", std::ofstream::out | std::ofstream::app);
        //std::ofstream::app, app = APPEND
    } else {
        Log::outputFile.open("log.txt", std::ofstream::out | std::ofstream::trunc);
        //std::ofstream::app, trunc = TRUNCATE
    }

    return Log::outputFile.is_open();
}

void zt::Log::close() {
    Log::outputFile.close();
}

void zt::Log::post(std::string tag, std::string message) {
    Log::outputFile << tag << "\t" << message << std::endl;
}

void zt::Log::error(std::string message) {
    Log::post("ERR", message);
}

void zt::Log::warning(std::string message) {
    Log::post("WAR", message);
}

void zt::Log::information(std::string message) {
    Log::post("INF", message);
}