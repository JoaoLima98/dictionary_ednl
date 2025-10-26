#include "linked_list.hpp"
#include <iostream>


LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void LinkedList::appendEnd(std::string eng, std::string pt, std::string clas) {
    Word* newWord = new Word(eng, pt, clas);

    if (head == nullptr) {
        head = newWord;
        tail = newWord;
    } else {
        tail->next = newWord;
        tail = newWord;
    }
    size++;
}

void LinkedList::printList() {
    if (head == nullptr) {
        std::cout << "A lista esta vazia." << std::endl;
        return;
    }
    std::cout << "\n--- Conteudo da Lista Encadeada ---" << std::endl;
    Word* current = head;
    
    int counter = 0;
    while (current != nullptr) {
        std::cout << "No " << ++counter << ": [" << current->english << "], [" 
                  << current->portuguese << "], [" << current->classification << "]" << std::endl;
        current = current->next;
    }
    std::cout << "------------------------------------" << std::endl;

    
}

Word LinkedList::removeAt(int index) {
    if (index < 0 || index >= size) {
        return Word("", "", "");
    }

    Word* current = head;
    Word* previous = nullptr;

    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current == tail) {
        tail = previous;
    }

    Word removedWord = *current;
    delete current;
    size--;

    return removedWord;
}