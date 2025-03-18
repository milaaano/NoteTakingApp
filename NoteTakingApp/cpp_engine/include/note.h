#ifndef NOTE_H
#define NOTE_H

#include <string>

struct Note {
    long long id;
    std::string content;
    std::string snippet;
    long long score;

    Note() : id(0), score(0) {}
};

#endif