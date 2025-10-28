#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <limits> // Necessário para limpar o buffer de entrada (cin)

#include "linked_list.hpp"
#include "bst.hpp"

void printMenu() {
    std::cout << "\n--- Dicionario Ingles <-> Portugues ---" << std::endl;
    std::cout << "1: Adicionar nova palavra" << std::endl;
    std::cout << "2: Buscar palavra (em Ingles)" << std::endl;
    std::cout << "3: Remover palavra (em Ingles)" << std::endl;
    std::cout << "4: Listar em ordem alfabetica (Em-Ordem)" << std::endl;
    std::cout << "5: Listar por nivel (Em-Largura)" << std::endl;
    std::cout << "0: Sair" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

// --- Função Auxiliar para Limpar o 'cin' ---
// Evita loops infinitos se o usuário digitar uma letra em vez de um número.
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::ifstream file("words.txt");
    if (!file.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo 'words.txt'." << std::endl;
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

    BinarySearchTree myDictionary;
    srand(time(0));
    std::cout << "Transferindo da lista para a arvore de forma aleatoria..." << std::endl;
    while (words_list.size > 0) {
        int randomIndex = rand() % words_list.size;
        Word removedWord = words_list.removeAt(randomIndex);
        myDictionary.insert(removedWord.english, removedWord.portuguese, removedWord.classification);
    }
    std::cout << "Transferencia concluida! Dicionario pronto para uso." << std::endl;
    
    int choice = -1;
    std::string eng, pt, clas;

    while (true) {
        printMenu();
        std::cin >> choice;

        // Checagem de segurança/suporte para entrada inválida no menu (ex: usuário digita 'a')
        if (std::cin.fail()) {
            std::cout << "Erro: Por favor, digite apenas numeros." << std::endl;
            std::cin.clear();
            clearInputBuffer();
            choice = -1; // Reseta a escolha para evitar o 'default'
        }

        switch (choice) {
            case 1:
                std::cout << "Digite a palavra em Ingles: ";
                clearInputBuffer(); // Limpa o '\n' deixado pelo 'cin >> choice'
                std::getline(std::cin, eng);
                std::cout << "Digite a traducao em Portugues: ";
                std::getline(std::cin, pt);
                std::cout << "Digite a classificacao (substantivo, verbo, etc.): ";
                std::getline(std::cin, clas);
                
                myDictionary.insert(eng, pt, clas);
                std::cout << "Palavra '" << eng << "' adicionada com sucesso!" << std::endl;
                break;

            case 2:
                std::cout << "Digite a palavra em Ingles para buscar: ";
                clearInputBuffer();
                std::getline(std::cin, eng);
                
                myDictionary.printSelectedWord(eng);
                break;

            case 3:
                std::cout << "Digite a palavra em Ingles para remover: ";
                clearInputBuffer();
                std::getline(std::cin, eng);
                
                if (myDictionary.printSelectedWord(eng))
                {
                    myDictionary.remove(eng);
                    std::cout << "Palavra '" << eng << "' removida." << std::endl;
                }else{
                    std::cout << "Remocao cancelada." << std::endl;
                }
                break;
            case 4:
                myDictionary.printInOrder();
                break;

            case 5:
                myDictionary.printLevelOrder();
                break;

            case 0:
                std::cout << "Obrigado por usar o dicionario. Ate logo!" << std::endl;
                return 0;

            default:
                std::cout << "Opcao invalida. Por favor, tente novamente." << std::endl;
                break;
        }
    }

    return 0;
}