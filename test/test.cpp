#include <iostream>

using namespace std;

struct Node {
    int Key;
    Node *Left;
    Node *Right;
};

class Tree {
private:
    Node *Root; //Указатель на корень дерева.
public:
    Tree() { Root = NULL; };

    void PrintTree(Node *, int);

    void FibonTree1(int, Node **);

    void FibonTree2(Node **, int *);

    Node **GetTree() { return &Root; };

    Node *GetTree1() { return Root; };
};

void Tree::PrintTree(Node *W, int l) {
    int i;

    if (W != NULL) {
        PrintTree(W->Right, l + 1);
        for (i = 1; i <= l; i++) cout << "   ";
        cout << W->Key << endl;
        PrintTree(W->Left, l + 1);
    }
}

void Tree::FibonTree1(int k, Node **T)
// Построение дерева Фибоначчи порядка k с незаполненными
// полями Key узлов.
{
    if (k == 0) (*T) = NULL;
    else if (k == 1) {
        (*T) = new (Node);
        (*T)->Left = (*T)->Right = NULL;
    } else {
        (*T) = new (Node);
        FibonTree1(k - 1, &((*T)->Left));
        FibonTree1(k - 2, &((*T)->Right));
    }
}

void Tree::FibonTree2(Node **T, int *i)
// Заполнение поля Key узлов дерева Фибоначчи.
{
    if ((*T) != NULL) {
        FibonTree2(&((*T)->Left), i);
        (*T)->Key = (*i);
        (*i)++;
        FibonTree2(&((*T)->Right), i);
    }
}

int main() {
    Tree A;
    int k;
    cout << "Вводите k...";
    cin >> k;
    int i = 1; // Инициализация самого левого ключа дерева.
    A.FibonTree1(k, A.GetTree());
    A.FibonTree2(A.GetTree(), &i);
    A.PrintTree(A.GetTree1(), 0);

    return 1;

}