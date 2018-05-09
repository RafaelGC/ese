#include <Zelta/Internationalization/TextContainer.hpp>
#include <iostream>

namespace zt {
    
    TextContainer::TextContainer() {
        currentLanguageSet = false;
    }
    
    TextContainer::TextContainer(const std::string& file, const std::wstring& language) {
        in(language);
    }

    TextContainer::TextContainer(const std::string& file) {
        currentLanguageSet = false;
        load(file);
    }

    TextContainer& TextContainer::in(const std::wstring& language) {
        currentLanguage = language;
        currentLanguageSet = true;
        
        return *this;
    }

    void TextContainer::load(const std::string& file, std::wstring language) {
        fLoad(file, language, true);
    }
    
    /**
     * @brief Loads the string in all languages.
     */
    void TextContainer::load(const std::string& file) {
        fLoad(file, L"", false);
    }
    
    void TextContainer::fLoad(const std::string& file, const std::wstring& language, bool onlyLanguage) {
        pugi::xml_document doc;
        in(language);

        if (!doc.load_file(file.c_str())) {
            return;
        }

        for (pugi::xml_node stringNode = doc.first_child(); stringNode; stringNode = stringNode.next_sibling()) {
            
            if (wcscmp(stringNode.name(), L"string") == 0) {
                
                std::wstring stringName = stringNode.attribute(L"name").value();
                
                for (pugi::xml_node transNode = stringNode.first_child(); transNode; transNode = transNode.next_sibling()) {
                    
                    std::wstring lang = transNode.attribute(L"lang").value();
                    
                    if ((onlyLanguage && lang == language) || !onlyLanguage) {
                        texts[stringName][lang] =  transNode.text().as_string();
                    }
                    
                }
            }
        }
    }

    /**
     * @brief Returns a string by its name.
     * @param name Name of the string we want to be returned.
     * @param defaultValue String that will be returned if the string
     * is not defined.
     * @return The translated string in the current language.
     * */
    const std::wstring& TextContainer::get(const std::wstring& stringName, const std::wstring& defaultValue) {
        if (texts.count(stringName) && texts[stringName].count(currentLanguage)) {
            return texts[stringName][currentLanguage];
        }
        else {
            return defaultValue;
        }
    }

    /**
     * @brief Returns a string by its name.
     * @param name Name of the string we want to be returned.
     * @return The translated string in the current language.
     * */
    const std::wstring& TextContainer::get(const std::wstring& stringName) {
        return texts[stringName][currentLanguage];
    }
    
    /**
     * @brief 
     */
    const std::wstring& TextContainer::operator[](const std::wstring& stringName) {
        return get(stringName);
    }

    /**
     * @return Returns the current language.
     * */
    std::wstring TextContainer::getCurrentLanguage() {
        return currentLanguage;
    }
    
}