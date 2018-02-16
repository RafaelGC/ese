#include <Zelta/Core/FileLog.hpp>

namespace zt {
    
    FileLog::FileLog() {
        mOpen = false;
    }
    
    FileLog::FileLog(const std::string& filename, Mode mode) {
        open(filename, mode);
    }
    
    FileLog::~FileLog() {
        if (mOpen) {
            outputFile.close();
        }
    }
    
    bool FileLog::open(const std::string& filename, Mode mode) {
        if (mode == Mode::KEEP_PREVIOUS_LOG) {
            outputFile.open(filename, std::ofstream::out | std::ofstream::app);
        } else {
            outputFile.open(filename, std::ofstream::out | std::ofstream::trunc);
        }

        mOpen = outputFile.is_open();
        
        return mOpen;
    }

    void FileLog::close() {
        if (mOpen) {
            outputFile.close();
            
            mOpen = false;
        }
    }

    void FileLog::log(Type type, const std::string& message) {
        if (mOpen) {
            if (type == Type::INFO) {
                outputFile << "INFO:\t" << message << std::endl;
            }
            else if (type == Type::SUCCESS) {
                outputFile << "SUCCESS:\t" << message << std::endl;
            }
            else if (type == Type::WARNING) {
                outputFile << "WARNING:\t" << message << std::endl;
            }
            else if (type == Type::ERROR) {
                outputFile << "ERROR:\t" << message << std::endl;
            }
        }
    }
    
    FileLog& FileLog::operator <<(const std::string& message) {
        log(lastMode, message);
        return (*this);
    }
    
    FileLog& FileLog::operator <<(const Log::Type& type) {
        lastMode = type;
        return *this;
    }
}