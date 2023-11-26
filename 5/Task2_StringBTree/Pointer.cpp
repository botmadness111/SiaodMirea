//
// Created by Andre on 19.11.2023.
//

using namespace std;

class TreeNode;

class Pointer {
public:
    TreeNode *myNode = nullptr;
    TreeNode *next = nullptr;
    string val;


    Pointer(TreeNode *next, string val, TreeNode *myNode) {
        this->next = next;
        this->val = val;
        this->myNode = myNode;
    }

    Pointer(){}

    // Перегрузка оператора < для сравнения объектов
    bool operator<(const Pointer& other) const {
        return val < other.val;
    }


};
