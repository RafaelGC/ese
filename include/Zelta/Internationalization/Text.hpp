#ifndef TEXT_HPP
#define TEXT_HPP

#include <cstring>
#include <map>

#include <Zelta/External/pugixml.hpp>

namespace zt {

    class Text {
    public:
        Text();

        /**
         * @brief Loads the strings in certain language.
         * @param file XML filename.
         * @param language Language tha will be loaded from the XML.
         */
        Text(const std::string& file, const std::wstring& language);

        /**
         * @brief Loads the string in all languages.
         */
        Text(const std::string& file);

        /**
         * @brief Sets the default language in which the strings will
         * be returned.
         * @param file XML filename.
         */
        Text& in(const std::wstring& language);

        /**
         * @brief Loads the strings in certain language.
         * @param file XML filename.
         * @param language Language tha will be loaded from the XML.
         */
        void load(const std::string& file, std::wstring language);

        /**
         * @brief Loads the string in all languages.
         */
        void load(const std::string& file);

        /**
         * @brief Returns a string by its name.
         * @param name Name of the string we want to be returned.
         * @param defaultValue String that will be returned if the string
         * is not defined.
         * @return The translated string in the current language.
         * */
        std::wstring get(const std::wstring& stringName, const std::wstring& defaultValue);

        /**
         * @brief Returns a string by its name.
         * @param name Name of the string we want to be returned.
         * @return The translated string in the current language.
         * */
        std::wstring get(const std::wstring& stringName);

        /**
         * @return Returns the current language.
         * */
        std::wstring getCurrentLanguage();

    protected:
        // map[stringname => map[lang => text]]
        std::map<std::wstring, std::map<std::wstring, std::wstring>>texts;

        std::wstring currentLanguage;
        bool currentLanguageSet;
        
        void fLoad(const std::string& file, const std::wstring& language, bool onlyLanguage);
    };

}

#endif