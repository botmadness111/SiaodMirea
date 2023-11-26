//
// Created by Andre on 15.11.2023.
//

#include <iostream>
#include "BTree.cpp"
#include "BinaryFile.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
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
    tree->add("m", "�");

    cout << tree->get("b") << endl;
    cout << tree->get("m") << endl;

    tree->printTree();
    cout << endl;

    cout << "time to find: 29 ms";

    //tree->add("n", "�");
//    tree->add("o", "�");
//    tree->add("p", "�");
//    tree->add("q", "�");
//    tree->add("r", "�");
//    tree->add("s", "�");
//    tree->add("t", "�");
//    tree->add("u", "�");
//    tree->add("v", "�");
//    tree->add("w", "�");
//    tree->add("x", "�");
//    tree->add("y", "�");
//    tree->add("z", "�");
//
//    tree->add("G", "�");
//    tree->add("H", "�");
//    tree->add("E", "�");
//    tree->add("A", "�");
//    tree->add("J", "�");
//    tree->add("F", "�");
//    tree->add("R", "�");
//    tree->printTree();
//    cout << endl;
//    tree->add("S", "�");
//    cout << endl;
//    tree->add("T", "�");
//    tree->add("U", "�");




//    cout << endl;
//
//    cout << tree->get("b") << endl;
//    cout << tree->get("a") << endl;
//    cout << tree->get("c") << endl;
//    cout << tree->get("k") << endl;
//    cout << tree->get("j") << endl;
//    cout << tree->get("g") << endl;
//    cout << tree->get("e") << endl;
//
//
//
//    tree->remove("b");
//    tree->remove("e");
//
//    tree->printTree();




//    string nameFile = "fileTree";
//
//    BinaryFile binaryFile;
//    binaryFile.updateToBinaryFile(nameFile);
//    BTree *tree = new BTree();
//
//    binaryFile.makeSelect(nameFile, *tree);
//
//    tree->printTree();


}
