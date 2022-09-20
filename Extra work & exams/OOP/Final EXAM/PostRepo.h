//
// Created by bia on 06/07/2022.
//

#ifndef E_RETAKE_BIA1708_POSTREPO_H
#define E_RETAKE_BIA1708_POSTREPO_H

#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include "Post.h"
#include "User.h"
#include "Observer.h"

class PostRepo : public Subject {
private:
    std::vector<Post> posts;
public:
    PostRepo() { this->readFromFile(); }

    void readFromFile();
    void writeToFile();

    void add(const Post& p) { this->posts.push_back(p); this->notify(); }
    void update(Post& p, const std::string& txt);

    void sortMe();
    void sort(std::vector<Post> v);

    std::vector<Post> getAll() { return this->posts; }
    std::vector<Post> getByUser(User u);
    std::vector<Post> getByString(std::string str);
    Post& operator[](int i) { return this->posts[i]; }

};


#endif //E_RETAKE_BIA1708_POSTREPO_H
