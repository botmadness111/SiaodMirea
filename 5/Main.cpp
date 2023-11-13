//
// Created by Andre on 12.11.2023.
//

#include <iostream>
#include "BinarySerachTree.cpp"
#include "BinaryFile.cpp"

using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");
    string nameFile = "fileTree";

    BinaryFile binaryFile;
    binaryFile.updateToBinaryFile(nameFile);

    BinarySearchTree *tree = new BinarySearchTree();
    binaryFile.makeSelect(nameFile, *tree);

    cout << tree->get("Blue") << endl;


//    tree->add("cat", "кот");
//    tree->add("base", "база");
//
//    tree->add("azxcew", "ацхцев");
//    tree->add("dq", "дэйю");
//    tree->add("ff", "фф");
//    tree->add("case", "кейс");
//
//    tree->add("Agf", "Аджиф");
//    tree->add("Bx", "Бэкс");

    //cout << tree->get("Agf") << endl;;

    //tree->remove("cat");

    //tree->printTree();


    return 1;

}
