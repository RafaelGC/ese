/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Package.hpp
 * Author: rafa
 *
 * Created on February 9, 2018, 11:11 PM
 */

#ifndef ZELTALIB_PACKAGE_HPP
#define ZELTALIB_PACKAGE_HPP

#include <fstream>
#include <map>
#include <stdint.h>
#include <vector>

namespace zt {
    
    // Helper class to store file metadata.
    class PackageFileInfo {
    public:
        unsigned long position;
        unsigned long size;
        PackageFileInfo() { position = size = 0l; };
        PackageFileInfo(unsigned long position, unsigned long size) : 
        position(position), size(size) { }
    };
    
    /**
     * @brief The Package class allows you to store all your assets (images,
     * sounds, fonts) in the same file. The class also let you load those
     * files from the package easily.
     * 
     * The package use a custom format called ZPKG (ZeltaLib Package).
     * A ZPKG file has a 12 bytes header.
     * -The first four bytes are the magic number (ZPKG codified in ASCII).
     * -The next four bytes represent the version of the format (1, at the moment).
     * -The last four bytes represent the compression used. At the moment this
     * library does not compress the data (a zero is written).
     * 
     * After the header, we can have zero or more files stored in the package.
     * Each file is composed of a header and the actual data. The header takes
     * 8 bytes to represent the file size and 512 more bytes to represent the
     * file name and path.
     */
    class Package {
    public:
        
        static const unsigned int COMPRESSION_NONE = 0;
        
        Package();
        ~Package();
        
        /**
         * @brief Creates a new empty package.
         * @param Name of the package. You may consider using the .zpkg extension.
         * @param compression The compression is not supported at the moment.
         */
        void create(const std::string& file, unsigned int compression = COMPRESSION_NONE);
        
        /**
         * @brief Opens an existing package.
         * 
         * When you open a package the whole file is read to build an index.
         * Note that, despite having been read, it has not been loaded on memory.
         * The index will help the class to find the files you request faster.
         * @param file
         */
        void open(const std::string& file);
        
        /**
         * @brief Adds a file to the package.
         * @param input Input file.
         * @param target Path and name of the file inside the package.
         */
        void addFile(const std::string& input, const std::string& target);
        
        /**
         * @brief Adds the content of a directory to the package.
         * @warning It's just implemented in Linux.
         * @param file
         */
        void addDirectory(const std::string& directory);
        
        /**
         * @brief Removes a file from the package.
         * This is an expensive task which involves reading the whole
         * package and writing it again without the removed file.
         * @param file Name of the file in the package.
         */
        void removeFile(const std::string& file);
        
        /**
         * Returns all file names in the package.
         * @return 
         */
        std::vector<std::string> getNames() const;
        
        /**
         * Returns the bytes (uint8_t) of a file.
         * @param file File name.
         * @return Vector of bytes.
         */
        std::vector<uint8_t> getFileData(const std::string& file);
        
        /**
         * Returns the size of a file in bytes.
         * @param file
         * @return 
         */
        unsigned long getFileSize(const std::string& file);
        
    protected:
        std::fstream file;
        std::string packageName;
        std::map<std::string, PackageFileInfo> fileIndex;
        
        // Bytes used to store the name of a file.
        const unsigned int NAME_BYTES = 512;
        
        // Bytes used to store the file size.
        // Note that in the code I use unsigned long to represent this size.
        // That means that if you want to increase SIZE_BYTES you should consider
        // use a different datatype.
        const unsigned int SIZE_BYTES = 8;
        
        const unsigned int VERSION = 1;
        
        const char* MAGIC_NUMBER = "ZPKG";
        
    };
}

#endif /* PACKAGE_HPP */

