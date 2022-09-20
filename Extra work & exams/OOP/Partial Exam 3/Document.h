//
// Created by bia on 26/05/2022.
//

#ifndef T3_BIA1708_DOCUMENT_H
#define T3_BIA1708_DOCUMENT_H
#include <iostream>
#include <vector>

class Document {
private:
    std::string name;
    std::vector<std::string> keywords;
    std::string content;
public:
    Document(const std::string &name, const std::vector<std::string> &keywords, const std::string &content);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::vector<std::string> &getKeywords() const;

    void setKeywords(const std::vector<std::string> &keywords);

    const std::string &getContent() const;

    void setContent(const std::string &content);
};


#endif //T3_BIA1708_DOCUMENT_H
