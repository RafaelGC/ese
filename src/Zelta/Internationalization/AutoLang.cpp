/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <SFML/Graphics/Text.hpp>

#include <Zelta/Internationalization/AutoLang.hpp>

namespace zt {
    AutoLang::AutoLang() {
        textSource = nullptr;
        langSet = false;
    }

    AutoLang::AutoLang(zt::Text& textSource) {
        setTextSource(textSource);
    }

    void AutoLang::setTextSource(zt::Text& textSource) {
        this->textSource = &textSource;

        updateAll();
    }

    void AutoLang::bind(sf::Text& text, const std::wstring& stringName) {
        bindedTexts.push_back(std::make_pair(&text, stringName));

        pushLangState();
        updateText(&text, stringName);
        popLangState();
    }

    void AutoLang::setLanguage(const std::wstring& lang) {
        this->langSet = true;
        this->language = lang;

        updateAll();
    }

    void AutoLang::updateAll() {
        if (!canUpdate()) return;

        pushLangState();

        for (auto& btext : this->bindedTexts) {
            updateText(btext.first, btext.second);
        }

        popLangState();
    }

    void AutoLang::updateText(sf::Text* text, const std::wstring& stringName) {
        if (!canUpdate()) return;

        text->setString(this->textSource->get(stringName));
    }

    bool AutoLang::canUpdate() const {
        return textSource && langSet;
    }

    void AutoLang::pushLangState() {
        if (langSet) {
            this->oLanguage = this->textSource->getCurrentLanguage();
            this->textSource->in(this->language);
        }
    }

    void AutoLang::popLangState() {
        if (langSet) {
            this->textSource->in(this->oLanguage);
        }
    }

}