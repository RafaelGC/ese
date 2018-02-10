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
    
    // Clase auxiliar.
    class PackageFileInfo {
    public:
        unsigned long position;
        unsigned long size;
        PackageFileInfo() { position = size = 0l; };
        PackageFileInfo(unsigned long position, unsigned long size) : 
        position(position), size(size) { }
    };
    
    /*
     * ESTRUCTURA DEL FICHERO ZPKG
     * [4 bytes] Número mágico
     * [4 bytes] Versión.
     * [4 bytes] Compresión.
     * Además, el fichero ZPKG está compuesto por cero o más sucesiones de:
     * [8 bytes]    Tamaño del fichero (en bytes) = size
     * [512 bytes]  Nombre del fichero
     * [size bytes] Fichero.
     */
    
    /**
     * @brief La clase Package sirve para empaquetar archivos en un único fichero
     * ZPKG.
     */
    class Package {
    public:
        
        static const unsigned int COMPRESSION_NONE = 0;
        
        Package();
        ~Package();
        
        /**
         * Crea un nuevo paquete vacío.
         * @param Nombre del paquete. Se recomienda usar la extensión .zpkg
         * @param compression Compresión a utilizar.
         */
        void create(const std::string& file, unsigned int compression = COMPRESSION_NONE);
        
        /**
         * Abre un paquete existente.
         * @param file
         */
        void open(const std::string& file);
        
        /**
         * Añade un fichero al paquete.
         * @param input Fichero de entrada.
         * @param target Nombre del fichero en el paquete.
         */
        void addFile(const std::string& input, const std::string& target);
        
        /**
         * Devuelve el contenido (bytes) de un fichero que esté en el paquete.
         * @param file Nombre del fichero en el paquete.
         * @return Vector de bytes.
         */
        std::vector<uint8_t> getFileData(const std::string& file);
        unsigned long getFileSize(const std::string& file);
        
    protected:
        std::fstream file;
        std::map<std::string, PackageFileInfo> fileIndex;
        
        // Bytes destinados a almacenar el nombre del fichero.
        const unsigned int NAME_BYTES = 512;
        
        // Bytes destinados a almacenar el tamaño del fichero.
        // Nota: en el código se usa unsigned long para representar este tamaño.
        // Si se quisiera ampliar SIZE_BYTES habría que utilizar otro tipo más grande.
        const unsigned int SIZE_BYTES = 8;
        
        const unsigned int VERSION = 1;
        
        const char* MAGIC_NUMBER = "ZPKG";
        
    };
}

#endif /* PACKAGE_HPP */

