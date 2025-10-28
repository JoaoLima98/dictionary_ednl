#include "bst.hpp"
#include <iostream>
#include <queue>

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

void BinarySearchTree::insert(std::string eng, std::string pt, std::string clas) {
    root = insertRecursive(root, eng, pt, clas);
}

void BinarySearchTree::printInOrder() {
    std::cout << "\n--- Dicionário Percurso Em-Ordem ---" << std::endl;
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
bool BinarySearchTree::printSelectedWord(std::string eng) {

    TreeNode* result = searchRecursive(root, eng);

    if (result == nullptr) {
        std::cout << "\n Palavra '" << eng << "' nao encontrada no dicionario." << std::endl;
        return false;
    } else {
        std::cout << "\n --- Palavra Encontrada ---" << std::endl;
        std::cout << "Ingles: " << result->english << std::endl;
        std::cout << "Portugues: " << result->portuguese << std::endl;
        std::cout << "Classificacao: " << result->classification << std::endl;
        return true;
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

void BinarySearchTree::printLevelOrder() {
    std::cout << "\n--- Dicionario Percurso Em-Largura ---" << std::endl;

    if (root == nullptr) {
        std::cout << "A arvore esta vazia." << std::endl;
        return;
    }
    
    std::queue<TreeNode*> queue;

    queue.push(root);

    while (!queue.empty()) {
        
        // 4. Pega o primeiro nó da fila
        TreeNode* currentNode = queue.front();
        queue.pop();

        std::cout << "English: " << currentNode->english << std::endl;

        if (currentNode->left != nullptr) {
            queue.push(currentNode->left);
        }
        if (currentNode->right != nullptr) {
            queue.push(currentNode->right);
        }
    }
    std::cout << "-------------------------------------------------" << std::endl;
}

void BinarySearchTree::remove(std::string eng) {
    root = removeRecursive(root, eng);
}

TreeNode* BinarySearchTree::findMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* currentNode, std::string eng) {
    if (currentNode == nullptr) {
        return nullptr;
    }

    if (eng < currentNode->english) {
        currentNode->left = removeRecursive(currentNode->left, eng);
    } else if (eng > currentNode->english) {
        currentNode->right = removeRecursive(currentNode->right, eng);
    } 
  
    else {
        // CASO 1: folha
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            delete currentNode;
            return nullptr;
        }
        // CASO 2: Nó com 1 filho
        else if (currentNode->left == nullptr) {
            // Tem um filho na direita
            TreeNode* temp = currentNode->right;
            delete currentNode;
            return temp;
        }
        else if (currentNode->right == nullptr) {
            // Tem um filho na esquerda
            TreeNode* temp = currentNode->left;
            delete currentNode;
            return temp;
        }
        // CASO 3: Nó com 2 filhos
        else {

            TreeNode* successor = findMin(currentNode->right);
            
            currentNode->english = successor->english;
            currentNode->portuguese = successor->portuguese;
            currentNode->classification = successor->classification;

            currentNode->right = removeRecursive(currentNode->right, successor->english);
        }
    }
    return currentNode;
}