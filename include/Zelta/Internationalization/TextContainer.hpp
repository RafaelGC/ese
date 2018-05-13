#ifndef TEXT_HPP
#define TEXT_HPP

#include <cstring>
#include <map>

#include <Zelta/Export.hpp>
#include <Zelta/External/pugixml.hpp>

namespace zt {

    class EXPORT TextContainer {
    public:
        TextContainer();

        /**
         * @brief Loads the strings in certain language.
         * @param file XML filename.
         * @param language Language tha will be loaded from the XML.
         */
        TextContainer(const std::string& file, const std::wstring& language);

        /**
         * @brief Loads the string in all languages.
         */
        TextContainer(const std::string& file);

        /**
         * @brief Sets the default language in which the strings will
         * be returned.
         * @param file XML filename.
         */
        TextContainer& in(const std::wstring& language);

        /**
         * @brief Loads the strings in certain language.
         * @param file XML filename.
         * @param language Language tha will be loaded from the XML.
         */
        void loadFromFile(const std::string& file, std::wstring language);

        /**
         * @brief Loads the string in all languages.
         */
        void loadFromFile(const std::string& file);
        
        /**
         * @brief Setups the TextContainer from a string containing the LXML.
         * @param string String containing the LXML.
         * @param language Language to be loaded.
         */
        void loadFromString(const std::wstring& string, std::wstring language);
        
        /**
         * @brief Setups the TextContainer from a string
         * @param string String containing the LXML.
         */
        void loadFromString(const std::wstring& string);
        
        /**
         * @brief Setups the TextContainer from a buffer.
         * @param data
         * @param size
         */
        void loadFromMemory(const void* data, std::size_t size);
        
        /**
         * @brief Setups the TextContainer from a buffer.
         * @param data
         * @param size
         */
        void loadFromMemory(const void* data, std::size_t size, std::wstring language);

        /**
         * @brief Returns a string by its name.
         * @param name Name of the string we want to be returned.
         * @param defaultValue String that will be returned if the string
         * is not defined.
         * @return The translated string in the current language.
         * */
        const std::wstring& get(const std::wstring& stringName, const std::wstring& defaultValue);

        /**
         * @brief Returns a string by its name.
         * @param name Name of the string we want to be returned.
         * @return The translated string in the current language.
         * */
        const std::wstring& get(const std::wstring& stringName);
        
        /**
         * @brief Returns a string by its name.
         * @param stringName Name of the string to be returned.
         * @return The translated string in the current language.
         */
        const std::wstring& operator[](const std::wstring& stringName);

        /**
         * @return Returns the current language.
         * */
        std::wstring getCurrentLanguage();

    protected:
        // map[stringname => map[lang => text]]
        std::map<std::wstring, std::map<std::wstring, std::wstring>>texts;

        std::wstring currentLanguage;
        bool currentLanguageSet;
        pugi::xml_document doc;
        
        void memoryLoad(const void* buff, std::size_t size, const std::wstring& language, bool onlyLanguage);
        void fileLoad(const std::string& file, const std::wstring& language, bool onlyLanguage);
        void parse(const std::wstring& language, bool onlyLaguage);
        
    };

}

#endif