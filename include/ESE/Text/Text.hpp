#ifndef TEXT_HPP
#define TEXT_HPP

#include <cstring>
#include <map>

#include <ESE/External/pugixml.hpp>
#include <ESE/Core/Log.hpp>
namespace ESE {

    class Text {
    protected:
        /**
         * @brief Clave-valor*/
        std::map<std::wstring, std::wstring>content;
        /**
         *@brief Idioma que se ha elegido al cargar el texto.
         * */
        std::wstring currentLanguage;
    public:
        Text();
        /**
         * @brief Este constructor permite cargar el archivo .xml nada más lo llamemos.
         * @param file Archivo XML
         * @param language Lenguaje para ser cargado.
         * */
        Text(std::string file, std::wstring language);
        /**
         * @brief Carga e interpreta el archivo XML.
         * @param file Archivo XML
         * @param language Lenguaje para ser cargado.
         * */
        void load(std::string file, std::wstring language);
        /**
         * @brief Obtenemos el valor de la clase que enviamos como parámetro.
         * @param name Clave que buscaremos.
         * @return Valor relacionado con la clave que puede depender del idioma elegido.
         * */
        std::wstring getString(std::wstring name);
        /**
         * @return Devuelve el lenguaje actual.
         * */
        std::wstring getCurrentLanguage();
    };

}

#endif