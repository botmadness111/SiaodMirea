//
// Created by Andre on 15.11.2023.
//

#include <iostream>
#include "BTree.cpp"

using namespace std;

int main() {
    BTree *tree = new BTree();
    tree->add("g", "�");
    tree->add("h", "�");
    tree->add("e", "�");
    tree->add("a", "�");
    tree->add("j", "�");
    tree->add("f", "�");
    tree->add("k", "�");
    tree->add("l", "�");
    tree->add("i", "�");
    tree->add("b", "�");
    tree->add("c", "�");
    tree->add("d", "�");

    tree->printTree();
    cout << endl;

//    cout << tree->get("b") << endl;
//    cout << tree->get("a") << endl;
//    cout << tree->get("c") << endl;
//    cout << tree->get("k") << endl;
//    cout << tree->get("j") << endl;
//    cout << tree->get("g") << endl;
//    cout << tree->get("e") << endl;



    tree->remove("g");

    tree->printTree();

}
