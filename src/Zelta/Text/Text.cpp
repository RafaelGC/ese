#include <Zelta/Text/Text.hpp>
namespace zt {

    Text::Text() {

    }

    Text::Text(std::string file, std::wstring language) {
        load(file, language);
    }

    void Text::load(std::string file, std::wstring language) {
        content.clear();
        currentLanguage = language;

        pugi::xml_document doc;

        if (!doc.load_file(file.c_str())) {
            return;
        }

        for (pugi::xml_node node = doc.first_child(); node; node = node.next_sibling()) {
            
            //Nos interesa analizar los tags "language".
            if (wcscmp(node.name(), L"language") == 0) {

                //Y, de entre los muchos "language" que puede haber, nos interesa aquel cuyo name
                //sea el deseado por el usuario. Es decir, que si el programador quiere el idioma "EN"
                //sólo leeremos ese.
                if (wcscmp(node.attribute(L"name").value(), language.c_str()) == 0) {
                    //Ya hemos encontrado el idioma que nos interesa, el que ha especificado el programador
                    //en el argumento.

                    for (pugi::xml_node node_texto = node.first_child(); node_texto; node_texto = node_texto.next_sibling()) {
                        content[node_texto.attribute(L"name").value()] = node_texto.child_value();
                    }
                }
                if (wcscmp(node.attribute(L"name").value(), L"DEFAULT") == 0) {
                    //También nos interesa obtener los string DEFAULT porque serán valores globales
                    //que servirán a todos los lenguajes. Eso sí, tenemos que asegurarnos de que ese valor por defecto
                    //no sustituya a un elemento del otro idioma, porque los otros tienen prioridad.

                    //Igualmente, recorremos los elementos...
                    for (pugi::xml_node node_texto = node.first_child(); node_texto; node_texto = node_texto.next_sibling()) {
                        //Sólo que ahora nos aseguramos de que el string no esté añadido antes de añadirlo.
                        if (content.find(node_texto.attribute(L"name").value()) == content.end()) {
                            //No está, se añade.
                            content[node_texto.attribute(L"name").value()] = node_texto.child_value();
                        }

                    }
                }
            }
        }
    }

    std::wstring Text::getString(std::wstring name) {
        return content[name];
    }

    std::wstring Text::getCurrentLanguage() {
        return currentLanguage;
    }

}