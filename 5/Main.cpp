//
// Created by Andre on 12.11.2023.
//

#include <iostream>
#include "BinarySerachTree.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    BinarySearchTree *tree = new BinarySearchTree();
    tree->add("z");
    tree->add("b");

    tree->add("a");
    tree->add("d");
    tree->add("f");
    tree->add("c");

    tree->add("A");
    tree->add("B");



    tree->remove("b");

    tree->printTree();

    return 1;

}
