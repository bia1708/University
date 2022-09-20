//
// Created by bia on 26/05/2022.
//

#include "Document.h"

Document::Document(const std::string &name, const std::vector<std::string> &keywords, const std::string &content)
        : name(name), keywords(keywords), content(content) {}

const std::string &Document::getName() const {
    return name;
}

void Document::setName(const std::string &name) {
    Document::name = name;
}

const std::vector<std::string> &Document::getKeywords() const {
    return keywords;
}

void Document::setKeywords(const std::vector<std::string> &keywords) {
    Document::keywords = keywords;
}

const std::string &Document::getContent() const {
    return content;
}

void Document::setContent(const std::string &content) {
    Document::content = content;
}
