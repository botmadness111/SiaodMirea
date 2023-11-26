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
    tree->add("m", "ä");

    cout << tree->get("b") << endl;
    cout << tree->get("m") << endl;

    tree->printTree();
    cout << endl;

    cout << "time to find: 29 ms";

    //tree->add("n", "ä");
//    tree->add("o", "ä");
//    tree->add("p", "ä");
//    tree->add("q", "ä");
//    tree->add("r", "ä");
//    tree->add("s", "ä");
//    tree->add("t", "ä");
//    tree->add("u", "ä");
//    tree->add("v", "ä");
//    tree->add("w", "ä");
//    tree->add("x", "ä");
//    tree->add("y", "ä");
//    tree->add("z", "ä");
//
//    tree->add("G", "æ");
//    tree->add("H", "ø");
//    tree->add("E", "å");
//    tree->add("A", "à");
//    tree->add("J", "ú");
//    tree->add("F", "ô");
//    tree->add("R", "ä");
//    tree->printTree();
//    cout << endl;
//    tree->add("S", "ä");
//    cout << endl;
//    tree->add("T", "ä");
//    tree->add("U", "ä");




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
