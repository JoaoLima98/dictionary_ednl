#ifndef BST_HPP
#define BST_HPP

#include <string>

struct TreeNode {
    std::string english;
    std::string portuguese;
    std::string classification;

    TreeNode* left;
    TreeNode* right;

    
    TreeNode(std::string eng, std::string pt, std::string clas) {
        english = eng;
        portuguese = pt;
        classification = clas;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertRecursive(TreeNode* currentNode, std::string eng, std::string pt, std::string clas);
    void printInOrderRecursive(TreeNode* currentNode);
    TreeNode* searchRecursive(TreeNode* currentNode, std::string eng);
public:
    BinarySearchTree();
    
    void insert(std::string eng, std::string pt, std::string clas);
    void printInOrder();
    void printSelectedWord(std::string eng);
};

#endif