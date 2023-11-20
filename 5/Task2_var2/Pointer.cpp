//
// Created by Andre on 19.11.2023.
//

class TreeNode;

class Pointer {
public:
    TreeNode *myNode = nullptr;
    TreeNode *next = nullptr;
    int val;


    Pointer(TreeNode *next, int val, TreeNode *myNode) {
        this->next = next;
        this->val = val;
        this->myNode = myNode;
    }


};
