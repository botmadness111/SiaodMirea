//
// Created by Andre on 19.11.2023.
//

class TreeNode;

class Pointer {
public:
    TreeNode *next = nullptr;
    int val;


    Pointer(TreeNode *next, int val) {
        this->next = next;
        this->val = val;
    }


};
