/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileNotFoundException.hpp
 * Author: rafa
 *
 * Created on February 10, 2018, 3:56 PM
 */

#ifndef ZELTALIB_FILENOTFOUNDEXCEPTION_HPP
#define ZELTALIB_FILENOTFOUNDEXCEPTION_HPP

#include <exception>
#include <string>

namespace zt {
    class FileNotFoundException : public std::exception {
    public:
        FileNotFoundException() {}
        FileNotFoundException(const std::string& fileName) : fileName(fileName) {}

        const char* what() const noexcept {
            return fileName.c_str();
        }
    private:
        std::string fileName;
    };
}
#endif /* FILENOTFOUNDEXCEPTION_HPP */

