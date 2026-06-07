// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include  "tree.h"


PMTree::PMTree(std::vector<char> in) {
    root = new Node('*');
    depth = in.size();
    std::sort(in.begin(), in.end());
    build(root, in);
}

void PMTree::build(Node* node, std::vector<char>& avail) {
    for (size_t i = 0; i < avail.size(); ++i) {
        Node* child = new Node(avail[i]);
        std::vector<char> next_avail;
        for (size_t j = 0; j < avail.size(); ++j) {
            if (i != j) {
                next_avail.push_back(avail[j]);
            }
        }
        build(child, next_avail);
        node->children.push_back(child);
    }
}

void PMTree::destroy(Node* node) {
    for (Node* child : node->children) {
        destroy(child);
    }
    delete node;
}

PMTree::~PMTree() {
    destroy(root);
}

void traverseAll(PMTree::Node* node, std::vector<char>& current,
    std::vector<std::vector<char>>& result) {
    if (node->children.empty()) {
        if (!current.empty()) {
            result.push_back(current);
        }
        return;
    }
    for (PMTree::Node* child : node->children) {
        current.push_back(child->value);
        traverseAll(child, current, result);
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    traverseAll(tree.root, current, result);
    return result;
}

bool traverseForPerm1(PMTree::Node* node, int target, int& counter,
    std::vector<char>& path, std::vector<char>& result) {
    if (node->children.empty()) {
        if (!path.empty()) {
            counter++;
            if (counter == target) {
                result = path;
                return true;
            }
        }
        return false;
    }
    for (PMTree::Node* child : node->children) {
        path.push_back(child->value);
        if (traverseForPerm1(child, target, counter, path, result)) return true;
        path.pop_back();
    }
    return false;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num < 1) return {};
    int counter = 0;
    std::vector<char> path;
    std::vector<char> result;
    traverseForPerm1(tree.root, num, counter, path, result);
    return result;
}

int64_t factorial(int n) {
    int64_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    int n = tree.depth;
    int64_t total = factorial(n);
    if (num < 1 || num > total) return {};

    std::vector<char> result;
    PMTree::Node* curr = tree.root;
    int64_t k = num - 1;

    for (int i = n; i > 0; --i) {
        int64_t f = factorial(i - 1);
        int idx = k / f;
        k %= f;
        curr = curr->children[idx];
        result.push_back(curr->value);
    }
    return result;
}
