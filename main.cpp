#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "linked_list.hpp"
#include "bst.hpp"

int main() {
 
    std::ifstream file("words.txt");
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open 'words.txt'." << std::endl;
        return 1;
    }

    LinkedList words_list;
    std::cout << "Populando a lista..." << std::endl;

    std::string file_line;
    while (std::getline(file, file_line)) { 
        std::stringstream ss(file_line);
        std::string englishWord, portugueseWord, wordClassification;

        getline(ss, englishWord, ',');
        getline(ss, portugueseWord, ',');
        getline(ss, wordClassification);

        words_list.appendEnd(englishWord, portugueseWord, wordClassification);
    }
    
    file.close();
    std::cout << "Leitura do arquivo concluida! " << words_list.size << " palavras carregadas." << std::endl;

    //Transferência Aleatória da Lista para a Árvore


    BinarySearchTree myDictionary;

    //Inicia o gerador de números aleatórios
    srand(time(0));

    std::cout << "Transferindo da lista para a arvore de forma aleatoria..." << std::endl;


    while (words_list.size > 0) {
        //Sorteia uma posição (de 0 até o tamanho atual - 1)
        int randomIndex = rand() % words_list.size;
        
        // Remove a palavra da lista nessa posição
        Word removedWord = words_list.removeAt(randomIndex);
        
        myDictionary.insert(removedWord.english, removedWord.portuguese, removedWord.classification);
    }

    std::cout << "Transferencia concluida! A lista esta vazia." << std::endl;

    myDictionary.printInOrder();
    myDictionary.printSelectedWord("good");
    myDictionary.printSelectedWord("duck");

    return 0;
}