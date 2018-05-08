/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/Core/Package.hpp>
#include <Zelta/Core/ConsoleLog.hpp>
#include <Zelta/Core/FileNotFoundException.hpp>
#include <istream>
#include <cstring>
#ifdef __linux__
#include <dirent.h>
#include <sys/stat.h>
#endif

#include <iostream>
#include <queue>

namespace zt {
    
    Package::Package() {}
    
    void Package::create(const std::string& fileName, unsigned int compression) {
        packageName = fileName;
        
        file.open(fileName, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (!file.is_open()) throw FileNotFoundException(fileName);
        
        file.write(MAGIC_NUMBER, 4);
        file.write((char *)&VERSION, 4);
        file.write((char *)&compression, 4);
    }
    
    void Package::open(const std::string& fileName) {
        packageName = fileName;
        
        // Open the file en binary read/write mode.
        file.open(fileName, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::app);
        if (!file.is_open()) throw FileNotFoundException(fileName);
        
        // Instead of loading all files in memory when this method is called,
        // it just builds an index to be able to load files faster when the user
        // requests them.
        // The index relates the filename with its position and size.
        
        
        unsigned long position = 12; // 4 (MAGIC) + 4 (VERSION) + 4 (COMPRESSION)
        file.seekg(position);
        
        // For each file...
        while (!file.eof()) {
            
            unsigned long size;

            // 1. Get the file size. Note: the size does NOT include the size of the
            // filename.
            file.read((char *)&size, SIZE_BYTES);
            if (file.eof()) break;
            
            char name[NAME_BYTES];

            // 2. Read the name/path of the file.
            file.read(name, NAME_BYTES);
            if (file.eof()) break;
            
            
            // El cursor ahora mismo está en <<position>>, apuntando al inicio
            // del archivo empaquetado.
            
            // 3. Store the position and size of the file.
            // Note that <<position>> is NOT really pointing to the file but
            // to the file size. After the file size is the file name. That's
            // why we must calculate position + SIZE_BYTES + NAME_BYTES to
            // get the actual file position in our package.
            fileIndex[std::string(name)] = PackageFileInfo(position + NAME_BYTES + SIZE_BYTES, size);
            
            // We move the pointer to the next file header.
            position += size + SIZE_BYTES + NAME_BYTES;
            file.seekg(position);
            
        }
        
        // After reading the file fome error flags can be activated.
        // If we want to use <<file>> later (for example, with addFile()) those
        // error flags will give problems.
        // Calling file.clear() we avoid that.
        file.clear();
    }
    
    Package::~Package() {
        if (file.is_open()) file.close();
    }
    
    void Package::addFile(const std::string& input, const std::string& target) {
        // At the moment, Package just supports adding files to the package.
        // It does not allow you to modify an existing file. So, if the user
        // is trying to add an existing file, we return:
        if (fileIndex.count(target) > 0 || !file.is_open()) {
            return;
        }
        
        std::ifstream newFile;
        
        // The file is open in binary read mode. The pointer is located at the
        // end of the file.
        newFile.open(input, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
        if (!newFile.is_open()) throw FileNotFoundException(input);
        
        // Since the pointer is at the end, tellg() tells us the size of the file.
        unsigned long size = newFile.tellg();
        
        // We move the pointer at the beginning.
        newFile.seekg(0);
        
        // In the output file, we move the cursor at the end of the file.
        // We will write the new file there.
        file.seekg(0, std::ios_base::end);
        
        // Write the size of the file.
        file.write((const char *)&size, SIZE_BYTES);
        
        // The filename is going to be stored temporarily in an array.
        char name[NAME_BYTES];
        // We clean the memory.
        std::memset(name, 0, NAME_BYTES);
        // Then we copy the name.
        std::memcpy(name, target.c_str(), target.size());
        // And we write it on the file.
        file.write(name, NAME_BYTES);
        // Note: writing just file.write(target.c_str(), NAME_BYTES) can give
        // problems if target.size() < NAME_SIZE because the memory could be dirty.
        
        // The pointer is still pointing at the beginning of the file. It's the
        // right moment to add the new file to the index:
        fileIndex[std::string(target)] = PackageFileInfo(file.tellp(), size);
        
        char byte;
        
        // Finally, we copy the contents of the file in the package.
        while (!newFile.eof()) {
            newFile.read(&byte, 1);
            if (newFile.eof()) break;
            file.write((const char *)&byte, 1);
        }
        
        newFile.close();
        
        file.clear();
    }
    
    /**
     * @brief Add a whole directory to the package.
     * @param directory
     */
    void Package::addDirectory(const std::string& directory) {
#if __linux__
        std::queue<std::string> pendantDirectories;
        std::string currentDirectory;
        std::string currentEntry;
        std::vector<std::string> files;
        
        pendantDirectories.push(directory);
        
        while (!pendantDirectories.empty()) {
            currentDirectory = pendantDirectories.front();
            pendantDirectories.pop();
            
            // List all entries of the current directory.
            DIR* dirp = opendir(currentDirectory.c_str());
            dirent* dp;
            while ((dp = readdir(dirp)) != NULL) {
                /*
                 * We list every entry. If it's a file we'll have to add it to
                 * the package, it it's a directory we'll add it to the list
                 * of pendant directories.
                 */
                currentEntry = std::string(dp->d_name);

                // Current and parent directories are ignored.
                if (currentEntry == "." || currentEntry == "..") continue;

                struct stat statbuf;
                
                if (stat(std::string(currentDirectory + "/" + currentEntry).c_str(), &statbuf) != 0) {
                    // Error: not existing file? permissions?
                    continue;
                }
                
                // Check if it's a file or a directory.
                if (S_ISDIR(statbuf.st_mode)) {
                    pendantDirectories.push(currentDirectory + "/" + currentEntry);
                }
                else {
                    files.push_back(currentDirectory + "/" + currentEntry);
                }
            }

            closedir(dirp);
        }
        
        for (const std::string& file : files) {
            // We ignore the ./ at the beginning of the file.
            addFile(file, (file[0] == '.' && file[1] == '/') ? file.substr(2) : file);
        }
        
#else
        throw std::exception("addDirectory() not implemented");
#endif
    }
    
    void Package::removeFile(const std::string& fileName) {
        if (!file.is_open()) return;
        if (fileIndex.count(fileName) == 0) throw zt::FileNotFoundException();
        
        /*
         * Removing a file from a package is difficult since we'll have to
         * reduce the size of the package.
         * C++ standard library does not come with any tool to do that so this
         * will be the strategy to remove a file:
         * 1. Create a new empty temporary file.
         * 2. Write in that file all the content of the package ignoring the
         * file we want to remove.
         * 3. Remove the old package.
         * 4. Rename the temporary file.
         */
        
        std::ofstream tmpFile;
        
        tmpFile.open(packageName + ".tmp", std::ios_base::trunc | std::ios_base::binary);
        if (!tmpFile.is_open()) throw zt::FileNotFoundException();
        
        // .position points to the beginning of the file but we also want to
        // get rid of the name and size:
        unsigned long ignoreFrom = fileIndex[fileName].position - NAME_BYTES - SIZE_BYTES;
        unsigned long ignoreTo = ignoreFrom + NAME_BYTES + SIZE_BYTES + fileIndex[fileName].size;
        
        // We copy the bytes that are before the file we want to remove.
        file.seekg(0);
        char byte;
        for (unsigned long i = 0; i < ignoreFrom; i++) {
            file.read(&byte, 1);
            tmpFile.write(&byte, 1);
        }
        
        // We cope the bytes that are after the file we want to remove.
        file.seekg(ignoreTo);
        while (!file.eof()) { // Copy until end is reached.
            file.read(&byte, 1);
            if (file.eof()) break;
            tmpFile.write(&byte, 1);
        }
        
        tmpFile.close();
        
        file.clear();
        
        // Remove the old file.
        file.close();
        std::remove(packageName.c_str());
        
        // Rename the temporal file.
        std::rename(std::string(packageName + ".tmp").c_str(), packageName.c_str());
        
        // Reopen the file (we need to rebuild the index).
        open(packageName);
    }
    
    std::vector<std::string> Package::getNames() const {
        std::vector<std::string> res;
        
        for (auto it = fileIndex.cbegin(); it != fileIndex.cend(); ++it) {
            res.push_back((*it).first);
        }
        return res;
    }
    
    unsigned long Package::getFileSize(const std::string& file) {
        return fileIndex[file].size;
    }
    
    /**
     * @brief Return the bytes of certain file.
     * @param fileName
     * @return Vector of bytes (uint8_t).
     */
    std::vector<uint8_t> Package::getFileData(const std::string& fileName) {
        std::vector<uint8_t> outputFile;
        
        if (fileIndex.count(fileName) == 0) throw FileNotFoundException(fileName);
        
        const PackageFileInfo inf = fileIndex[fileName];
        
        // We allocate enough space here:
        outputFile.reserve(inf.size);
        
        // Move the cursor to the file.
        file.seekg(inf.position, std::ios_base::beg);
        uint8_t r;
        // And copy the contents.
        for (unsigned long i = 0; i < inf.size; i++) {
            file.read((char *)&r, 1);
            outputFile.push_back(r);
        }
        
        return outputFile;
        
    }
    
    std::string Package::getFileDataAsString(const std::string& fileName) {
        // Check if file exists.
        if (fileIndex.count(fileName) == 0) throw FileNotFoundException(fileName);
        
        // Read its info from the index.
        const PackageFileInfo inf = fileIndex[fileName];
        
        // Move the cursor.
        file.seekg(inf.position, std::ios_base::beg);
        
        // Build the string.
        std::string result;
        result.reserve(inf.size);
        
        char r;
        for (unsigned long i = 0; i < inf.size; i++) {
            file.read(&r, 1);
            result.push_back(r);
        }
        
        return result;
    }
    
}