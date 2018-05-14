#include <Zelta/Internationalization/TextContainer.hpp>
#include <Zelta/Core/FileNotFoundException.hpp>
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
        loadFromFile(file);
    }

    TextContainer& TextContainer::in(const std::wstring& language) {
        currentLanguage = language;
        currentLanguageSet = true;
        
        return *this;
    }

    void TextContainer::loadFromFile(const std::string& file, std::wstring language) {
        fileLoad(file, language, true);
    }
    
    /**
     * @brief Loads the string in all languages.
     */
    void TextContainer::loadFromFile(const std::string& file) {
        fileLoad(file, L"", false);
    }
    
    void TextContainer::loadFromString(const std::wstring& string, std::wstring language) {
        const void* buff = string.c_str();
        
        memoryLoad(buff, string.size() * sizeof(wchar_t), language, true);
    }
    
    void TextContainer::loadFromString(const std::wstring& string) {
        const void* buff = string.c_str();
        
        memoryLoad(buff, string.size() * sizeof(wchar_t), L"", false);
    }
    
    void TextContainer::loadFromMemory(const void* buff, std::size_t size, std::wstring language) {
        memoryLoad(buff, size, language, true);
    }
    
    void TextContainer::loadFromMemory(const void* buff, std::size_t size) {
        memoryLoad(buff, size, L"", false);
    }
    
    void TextContainer::memoryLoad(const void* buff, std::size_t size, const std::wstring& language, bool onlyLanguage) {
        if (onlyLanguage) {
            in(language);
        }
        
        
        doc.load_buffer(buff, size);
        
        parse(language, onlyLanguage);
    }
    
    void TextContainer::fileLoad(const std::string& file, const std::wstring& language, bool onlyLanguage) {
        if (onlyLanguage) {
            in(language);
        }

        if (!doc.load_file(file.c_str())) {
            throw FileNotFoundException(file);
        }

        parse(language, onlyLanguage);
        
    }
    
    void TextContainer::parse(const std::wstring& language, bool onlyLanguage) {
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