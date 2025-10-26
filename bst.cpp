#include "bst.hpp"
#include <iostream>

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

void BinarySearchTree::insert(std::string eng, std::string pt, std::string clas) {
    root = insertRecursive(root, eng, pt, clas);
}

void BinarySearchTree::printInOrder() {
    std::cout << "\n--- Dictionary in Alphabetical Order (In-Order Traversal) ---" << std::endl;
    printInOrderRecursive(root);
    std::cout << "------------------------------------------------------------" << std::endl;
}

TreeNode* BinarySearchTree::insertRecursive(TreeNode* currentNode, std::string eng, std::string pt, std::string clas) {
    if (currentNode == nullptr) {
        return new TreeNode(eng, pt, clas);
    }

    if (eng < currentNode->english) {
        // Se for menor, continua a busca na sub-árvore esquerda.
        currentNode->left = insertRecursive(currentNode->left, eng, pt, clas);
    } else if (eng > currentNode->english) {
        // Se for maior, continua a busca na sub-árvore direita.
        currentNode->right = insertRecursive(currentNode->right, eng, pt, clas);
    }
    
    return currentNode;
}
void BinarySearchTree::printSelectedWord(std::string eng) {
    // Usa a mesma função auxiliar de antes para encontrar o nó
    TreeNode* result = searchRecursive(root, eng);

    if (result == nullptr) {
        std::cout << "Palavra '" << eng << "' nao encontrada no dicionario." << std::endl;
    } else {
        std::cout << "--- Palavra Encontrada ---" << std::endl;
        std::cout << "Ingles: " << result->english << std::endl;
        std::cout << "Portugues: " << result->portuguese << std::endl;
        std::cout << "Classificacao: " << result->classification << std::endl;
    }
}


TreeNode* BinarySearchTree::searchRecursive(TreeNode* currentNode, std::string eng) {
    if (currentNode == nullptr) {
        return nullptr;
    }
    if (eng == currentNode->english) {
        return currentNode;
    }
    if (eng < currentNode->english) {
        return searchRecursive(currentNode->left, eng);
    } else {
        return searchRecursive(currentNode->right, eng);
    }
}

void BinarySearchTree::printInOrderRecursive(TreeNode* currentNode) {
    if (currentNode != nullptr) {
        printInOrderRecursive(currentNode->left); // Primeiro, visita tudo à esquerda
        std::cout << "English: " << currentNode->english << std::endl; // Depois, visita o nó atual
        printInOrderRecursive(currentNode->right); // Por fim, visita tudo à direita (igual no exemplo do professor)
    }

}