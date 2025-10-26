#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <string>

struct Word {
    std::string english;
    std::string portuguese;
    std::string classification;
    Word* next;

    Word(std::string eng, std::string pt, std::string clas) {
        english = eng;
        portuguese = pt;
        classification = clas;
        next = nullptr;
    }
};

class LinkedList {
public:
    Word* head;
    Word* tail;
    int size;

    
    LinkedList();
    void appendEnd(std::string ing, std::string pt, std::string clas);
    void printList();
    Word removeAt(int index);
};

#endif