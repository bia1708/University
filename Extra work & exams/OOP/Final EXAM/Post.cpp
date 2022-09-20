//
// Created by bia on 06/07/2022.
//

#include "Post.h"

Post::Post(int id, const std::string &text, const timestamp &date, const std::string &user) : id(id), text(text),
                                                                                              date(date), user(user) {}

int Post::getId() const {
    return id;
}

void Post::setId(int id) {
    Post::id = id;
}

const std::string &Post::getText() const {
    return text;
}

void Post::setText(const std::string &text) {
    Post::text = text;
}

const timestamp &Post::getDate() const {
    return date;
}

void Post::setDate(const timestamp &date) {
    Post::date = date;
}

const std::string &Post::getUser() const {
    return user;
}

void Post::setUser(const std::string &user) {
    Post::user = user;
}
