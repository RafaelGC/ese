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
        
        // Abrir fichero para lectura/escritura y en modo binario.
        file.open(fileName, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::app);
        if (!file.is_open()) throw FileNotFoundException(fileName);
        
        // Durante la carga lo que se hace es crear un índice para tener
        // a mano todos los ficheros cuando lo solicite el usuario.
        // El índice relaciona el nombre del fichero que se quiere recuperar
        // con su posición y tamaño.
        
        
        unsigned long position = 12; // 4 (MAGIC) + 4 (VERSION) + 4 (COMPRESSION)
        file.seekg(position);
        
        while (!file.eof()) {
            
            unsigned long size;

            // Se lee el tamaño del fichero. Nota: el tamaño del fichero no incluye
            // el nombre del fichero.
            file.read((char *)&size, SIZE_BYTES);
            if (file.eof()) break;
            
            char name[NAME_BYTES];

            // Lectura del nombre del fichero.
            file.read(name, NAME_BYTES);
            if (file.eof()) break;
            
            
            // El cursor ahora mismo está en <<position>>, apuntando al inicio
            // del archivo empaquetado.
            fileIndex[std::string(name)] = PackageFileInfo(position + NAME_BYTES + SIZE_BYTES, size);
            
            // La próxima cabecera de fichero estará en position + size.
            position += size + SIZE_BYTES + NAME_BYTES;
            file.seekg(position);
            
        }
        
        // Después de haber leido se puede haber activado alguna bandera de error.
        // Si más adelante, por ejemplo, en el método addFile(), se intenta escribir
        // en el fichero no se podrá por culpa de este error.
        // Con .clear() se vuelve a la normalidad.
        file.clear();
    }
    
    Package::~Package() {
        if (file.is_open()) file.close();
    }
    
    void Package::addFile(const std::string& input, const std::string& target) {
        // Por ahora no se acepta la modificación de ficheros.
        // Si se trata de añadir un archivo que ya existe, ignora.
        if (fileIndex.count(target) > 0 || !file.is_open()) {
            return;
        }
        
        std::ifstream newFile;
        
        // Se abre el fichero en modo lectura y binario. Además el cursor
        // se sitúa al final del archivo.
        newFile.open(input, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
        if (!newFile.is_open()) throw FileNotFoundException(input);
        
        // Como el cursor está al final, tellg() indica el tamaño del fichero.
        unsigned long size = newFile.tellg();
        
        // Se mueve el cursor al inicio para comenzar la lectura.
        newFile.seekg(0);
        
        // Nos situamos al final del fichero de salida para
        // comenzar a escribir por el final.
        file.seekg(0, std::ios_base::end);
        
        // Se escribe el tamaño del fichero (se usan 8 bytes -> 64 bits).
        file.write((const char *)&size, SIZE_BYTES);
        
        // El nombre va a ser guardado en este array para ser escrito en el archivo:
        char name[NAME_BYTES];
        // Se limpia la memoria (puede haber basura).
        std::memset(name, 0, NAME_BYTES);
        // Y se copia el nombre.
        std::memcpy(name, target.c_str(), target.size());
        // Por último, se escribe.
        file.write(name, NAME_BYTES);
        // Nota: si pones file.write(target.c_str(), 512) y target tiene
        // una longitud menor que 512, el resto se puede rellenar con basura.
        
        // La posición de escritura actual apunta a la posición
        // donde se comienza a escribir el fichero dentro del paquete. Es un buen
        // momento para meter el fichero en el índice.
        fileIndex[std::string(target)] = PackageFileInfo(file.tellp(), size);
        
        char byte;
        
        // Se copia el contenido del fichero dentro del paquete.
        while (!newFile.eof()) {
            newFile.read(&byte, 1);
            if (newFile.eof()) break;
            file.write((const char *)&byte, 1);
        }
        
        newFile.close();
        
        file.clear();
    }
    
    
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
            
            // Listar las entradas del directorio actual.
            DIR* dirp = opendir(currentDirectory.c_str());
            dirent* dp;
            while ((dp = readdir(dirp)) != NULL) {
                // Listamos cada entrada. Si es un archivo
                // habrá que añadirlo al paquete, si es un directorio
                // habrá que añadirlo a la lista de directorios pendientes
                // para seguir expandiendo.
                currentEntry = std::string(dp->d_name);

                // El directorio actual y el padre no interesan.
                if (currentEntry == "." || currentEntry == "..") continue;

                // Comprobación de si la entrada es un fichero o un directorio.
                struct stat statbuf;
                if (stat(std::string(currentDirectory + "/" + currentEntry).c_str(), &statbuf) != 0) {
                    // Error con el archivo: ¿no existe? ¿permisos?
                    continue;
                }

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
            // Ignoramos el ./ del inicio del fichero.
            addFile(file, (file[0] == '.' && file[1] == '/') ? file.substr(2) : file);
        }
        
#else
        throw std::exception("addDirectory() not implemented");
#endif
    }
    
    void Package::removeFile(const std::string& fileName) {
        if (!file.is_open()) return;
        if (fileIndex.count(fileName) == 0) throw zt::FileNotFoundException();
        
        // Eliminar un fichero del paquete es una tarea compleja.
        // Es algo que generalmente implicará reducir el tamaño del paquete.
        // C++ no tiene ninguna utilidad estándar para reducir el tamaño del
        // fichero así que la aproximación que haré será la siguiente:
        // 1. Crear un nuevo fichero temporal vacío.
        // 2. Escribir en el fichero todo el contenido del paquete excluyendo
        // el archivo que se quiere eliminar.
        // 3. Eliminar el viejo paquete.
        // 4. Renombrar el fichero temporal para que tenga el nombre del paquete.
        
        std::ofstream tmpFile;
        
        tmpFile.open(packageName + ".tmp", std::ios_base::trunc | std::ios_base::binary);
        if (!tmpFile.is_open()) throw zt::FileNotFoundException();
        
        // .position apunta al inicio del fichero, pero también se quiere
        // eliminar el NOMBRE y el TAMAÑO.
        unsigned long ignoreFrom = fileIndex[fileName].position - NAME_BYTES - SIZE_BYTES;
        unsigned long ignoreTo = ignoreFrom + NAME_BYTES + SIZE_BYTES + fileIndex[fileName].size;
        
        // Copia de la parte anterior al fichero que se quiere eliminar.
        file.seekg(0);
        char byte;
        for (unsigned long i = 0; i < ignoreFrom; i++) {
            file.read(&byte, 1);
            tmpFile.write(&byte, 1);
        }
        
        // Copia de la parte posterior.
        file.seekg(ignoreTo);
        while (!file.eof()) { // Se copia hasta alcanzar el final.
            file.read(&byte, 1);
            if (file.eof()) break;
            tmpFile.write(&byte, 1);
        }
        
        tmpFile.close();
        
        file.clear();
        
        // Una vez generado completamente el archivo temporal se elimina el viejo.
        file.close(); // Antes de eliminarlo se cierra.
        std::remove(packageName.c_str());
        
        // Se renombra el temporal, que pasará a ser el definitivo.
        std::rename(std::string(packageName + ".tmp").c_str(), packageName.c_str());
        
        // Y se reabre el fichero (se volverá a reconstruir el índice).
        
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
    
    std::vector<uint8_t> Package::getFileData(const std::string& fileName) {
        std::vector<uint8_t> outputFile;
        
        if (fileIndex.count(fileName) == 0) throw FileNotFoundException(fileName);
        
        const PackageFileInfo inf = fileIndex[fileName];
        
        // Se reserva espacio suficiente desde el principio
        // para evitar que se tenga que hacer durante la copia.
        outputFile.reserve(inf.size);
        
        for (unsigned long currByte = inf.position; currByte < inf.position + inf.size; currByte++) {
            
            // Se sitúa el cursor en el byte correspondiente para leer.
            file.seekg(currByte, std::ios_base::beg);
            uint8_t r;
            file.read((char *)&r, 1);
            
            
            
            outputFile.push_back(r);
        }
        
        return outputFile;
        
    }
    
}