/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arguments.hpp
 * Author: rafa
 *
 * Created on January 22, 2018, 12:46 PM
 */

#ifndef ZELTALIB_ARGUMENTS_HPP
#define ZELTALIB_ARGUMENTS_HPP

#include <Zelta/Export.hpp>
#include <Zelta/Core/Argument.hpp>

#include <vector>

namespace zt {
    /**
     * @brief Represents a set of arguments (e.g.: the command line arguments).
     */
    class EXPORT Arguments {
    public:
        /**
         * @brief Crea un conjunto de parámetros vacío.
         */
        Arguments();

        /**
         * @brief Conjunto de parámetros a partir de un puntero de punteros.
         * @param argc Número de parámetros.
         * @param argv Puntero a cadenas de caracteres.
         */
        Arguments(int argc, char** argv);

        virtual void initialize(int argc, char** argv);

        /**
         * @return Número de parámetros.
         */
        int size() const;

        /**
         * @param i Índice del parámetro. El 0 debería ser el nombre del ejecutable.
         * @return Parámetro.
         */
        const Argument& get(int i) const;

        private:
        std::vector<Argument> args;
    };
}
#endif

