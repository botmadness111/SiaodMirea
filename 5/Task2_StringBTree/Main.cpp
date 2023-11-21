//
// Created by Andre on 15.11.2023.
//

#include <iostream>
#include "BTree.cpp"

using namespace std;

int main() {
    BTree *tree = new BTree();
    tree->add("g", "æ");
    tree->add("h", "ø");
    tree->add("e", "å");
    tree->add("a", "à");
    tree->add("j", "ú");
    tree->add("f", "ô");
    tree->add("k", "ê");
    tree->add("l", "ë");
    tree->add("i", "é");
    tree->add("b", "á");
    tree->add("c", "ñ");
    tree->add("d", "ä");

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
