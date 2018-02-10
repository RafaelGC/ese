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

namespace zt {
    
    Package::Package() {}
    
    void Package::create(const std::string& fileName, unsigned int compression) {
        file.open(fileName, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (!file.is_open()) throw FileNotFoundException(fileName);
        
        file.write(MAGIC_NUMBER, 4);
        file.write((char *)&VERSION, 4);
        file.write((char *)&compression, 4);
    }
    
    void Package::open(const std::string& fileName) {
        // Abrir fichero para lectura/escritura y en modo binario.
        file.open(fileName, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::app);
        if (!file.is_open()) throw FileNotFoundException(fileName);
        
        // Durante la carga lo que se hace es crear un índice para tener
        // a mano todos los ficheros cuando lo solicite el usuario.
        // El índice relaciona el nombre del fichero que se quiere recuperar
        // con su posición y tamaño.
        
        ZELTALIB_LOG_SUCCESS(zt::ConsoleLog(), "Open");
        
        
        unsigned long position = 12; // 4 (MAGIC) + 4 (VERSION) + 4 (COMPRESSION)
        file.seekg(position);
        
        while (!file.eof()) {
            ZELTALIB_LOG_SUCCESS(zt::ConsoleLog(), "Reading file...");
            
            unsigned long size;

            // Se lee el tamaño del fichero. Nota: el tamaño del fichero no incluye
            // el nombre del fichero.
            file.read((char *)&size, SIZE_BYTES);
            if (file.eof()) break;
            
            ZELTALIB_LOG_SUCCESS(zt::ConsoleLog(), "Size: " + std::to_string(size));
            
            char name[NAME_BYTES];

            // Lectura del nombre del fichero.
            file.read(name, NAME_BYTES);
            if (file.eof()) break;
            
            ZELTALIB_LOG_SUCCESS(zt::ConsoleLog(), name);
            
            // El cursor ahora mismo está en <<position>>, apuntando al inicio
            // del archivo empaquetado.
            fileIndex[std::string(name)] = PackageFileInfo(position + NAME_BYTES + SIZE_BYTES, size);
            
            // La próxima cabecera de fichero estará en position + size.
            position += size + SIZE_BYTES + NAME_BYTES + 1;
            ZELTALIB_LOG_WARNING(zt::ConsoleLog(), "Curr. position: " + std::to_string(position));
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
        if (fileIndex.count(target) > 0 || file.is_open()) {
            return;
        }
        
        std::ifstream newFile;
        
        // Se abre el fichero en modo lectura y binario. Además el cursor
        // se sitúa al final del archivo.
        newFile.open(input, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
        if (!newFile.is_open()) throw zt::FileNotFoundException(newFile);
        
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
        
        char byte;
        
        // Se copia el contenido del fichero.
        while (!newFile.eof()) {
            newFile.read(&byte, 1);
            file.write((const char *)&byte, 1);
        }
        
        newFile.close();
        
        file.clear();
        
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
        //outputFile.reserve(inf.size);
        
        zt::ConsoleLog().log(zt::Log::Type::SUCCESS, std::to_string(inf.position));
        
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