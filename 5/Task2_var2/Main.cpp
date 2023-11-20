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
    tree->add(0);
    tree->add(16);
    tree->add(7);
    tree->add(23);
    tree->add(48);
    tree->add(15);
    tree->add(1);
    tree->add(2);
    tree->add(3);
    tree->add(4);

}
