// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include "tree.h"

int main() {
    std::ofstream file("result/results.csv");
    if (!file) {
        std::cerr << "Folder result/ missing!" << std::endl;
        return 1;
    }

    file << "N,AllPerms,Perm1,Perm2\n";

    std::mt19937 gen(42);

    for (int n = 2; n <= 8; ++n) {
        std::vector<char> alphabet;
        for (int i = 0; i < n; ++i) {
            alphabet.push_back('1' + i);
        }

        PMTree tree(alphabet);

        int64_t fact = 1;
        for (int i = 2; i <= n; ++i) fact *= i;

        std::uniform_int_distribution<int64_t> dist(1, fact);
        int64_t targetNum = dist(gen);

        auto startAll = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto endAll = std::chrono::high_resolution_clock::now();

        auto start1 = std::chrono::high_resolution_clock::now();
        getPerm1(tree, targetNum);
        auto end1 = std::chrono::high_resolution_clock::now();

        auto start2 = std::chrono::high_resolution_clock::now();
        getPerm2(tree, targetNum);
        auto end2 = std::chrono::high_resolution_clock::now();

        auto dAll = std::chrono::
            duration_cast<std::chrono::microseconds>(endAll - startAll).count();
        auto d1 = std::chrono::
            duration_cast<std::chrono::microseconds>(end1 - start1).count();
        auto d2 = std::chrono::
            duration_cast<std::chrono::microseconds>(end2 - start2).count();

        file << n << "," << dAll << "," << d1 << "," << d2 << "\n";
        std::cout << "Processed N = " << n << std::endl;
    }
    file.close();
    return 0;
}
