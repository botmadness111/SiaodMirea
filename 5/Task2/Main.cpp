//
// Created by Andre on 15.11.2023.
//

#include <iostream>
#include "BTree.cpp"

using namespace std;

int main() {
    BTree *tree = new BTree();
    tree->add(8);
    tree->add(13);
    tree->add(5);
}
