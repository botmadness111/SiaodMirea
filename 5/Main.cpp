//
// Created by Andre on 12.11.2023.
//

#include <iostream>
#include "BinarySerachTree.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    BinarySearchTree *tree = new BinarySearchTree();
    tree->add("b");
    tree->add("a");
    tree->add("c");

    cout << tree->remove("a") << endl;
    cout << tree->remove("c") << endl;
    cout << tree->remove("b") << endl;

    return 1;

}
