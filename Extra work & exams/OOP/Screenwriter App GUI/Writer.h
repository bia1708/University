//
// Created by bia on 04/07/2022.
//

#ifndef SCREENWRITER_WRITER_H
#define SCREENWRITER_WRITER_H

#include <string>

class Writer {
public:
    std::string name, expertise;
private:
public:
    Writer(const std::string &name, const std::string &expertise);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getExpertise() const;

    void setExpertise(const std::string &expertise);
};


#endif //SCREENWRITER_WRITER_H
