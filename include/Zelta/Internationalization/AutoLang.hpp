/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AutoLang.hpp
 * Author: rafa
 *
 * Created on May 6, 2018, 9:32 PM
 */

#ifndef ZELTALIB_AUTOLANG_HPP
#define ZELTALIB_AUTOLANG_HPP

#include <Zelta/Internationalization/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <vector>

namespace zt {

    /**
     * @brief AutoLang is a tool which allows you to bind a sf::Text to a
     * zt::Text string. You can set a language for the AutoLang instance so that
     * all binded strings will be translated automatically.
     */
    class AutoLang {
    public:
        AutoLang();
        AutoLang(zt::Text& textSource);
        void setTextSource(zt::Text& textSource);
        void bind(sf::Text& text, const std::wstring& stringName);
        void setLanguage(const std::wstring& lang);
    protected:
        void updateAll();
        void updateText(sf::Text* text, const std::wstring& stringName);
        bool canUpdate() const;
        void pushLangState();
        void popLangState();
    private:
        std::vector<std::pair<sf::Text*, std::wstring>> bindedTexts;
        zt::Text* textSource;
        std::wstring language, oLanguage;
        bool langSet;
    };

}

#endif /* AUTOLANG_HPP */

