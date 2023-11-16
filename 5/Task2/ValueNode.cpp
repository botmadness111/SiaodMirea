//
// Created by Andre on 15.11.2023.
//


class TreeNode;

class ValueNode {
public:

    int value;
    ValueNode *right = nullptr;
    ValueNode *left = nullptr;

    ValueNode *rightOnLvl = nullptr;
    ValueNode *leftOnLvl = nullptr;

    TreeNode *myNode = nullptr;



    ValueNode(TreeNode *node) {
        this->myNode = node;
    }

    ValueNode(int val, TreeNode *node) {
        value = val;
        myNode = node;
    }


};
