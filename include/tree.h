// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

class PMTree {
 public:
    struct Node {
        char value;
        std::vector<Node*> children;
        explicit Node(char v) : value(v) {}
    };

    Node* root;
    int depth;

    explicit PMTree(std::vector<char> in);
    ~PMTree();

 private:
    void build(Node* node, std::vector<char>& avail);
    void destroy(Node* node);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
