#include <chrono>
#include "iostream"
#include "Tree.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Tree *tree = new Tree(1);
    tree->add(2);
    tree->add(3);
    tree->add(4);
    tree->add(6);
    tree->add(9);

    tree->print();

    cout << endl;
    cout << "-------------------------" << endl;

    vector<int> arrayChildrens = tree->getCountChildrens();
    for (int i = 0; i < arrayChildrens.size(); i++) {
        cout << arrayChildrens[i] << " ";
    }
    cout << endl;
    cout << "-------------------------" << endl;

    vector<int> arrayLvl = tree->getLvlNode();
    for (int i = 0; i < arrayLvl.size(); i++) {
        cout << arrayLvl[i] << " ";
    }

//    tree->removeLastLeft();
//    tree->removeLastLeft();
//    tree->removeLastLeft();

}
