//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_POST_H
#define E_RETAKE_BIA1708_POST_H

#include <string>

struct timestamp{
    int day, time;
};

class Post {
private:
    int id;
    std::string text;
    timestamp date;
    std::string user;
public:
    Post(int id, const std::string &text, const timestamp &date, const std::string &user);

    int getId() const;

    void setId(int id);

    const std::string &getText() const;

    void setText(const std::string &text);

    const timestamp &getDate() const;

    void setDate(const timestamp &date);

    const std::string &getUser() const;

    void setUser(const std::string &user);
};


#endif //E_RETAKE_BIA1708_POST_H
