//
// Created by Andre on 15.11.2023.
//

#include "TreeNode.cpp"

class BTree {
private:
    int const M = 3;
    TreeNode *head = nullptr;

public:
    void add(int val) {
        if (head == nullptr) {
            head = new TreeNode(val);
        } else {
            ValueNode *mid = head->getMidValueNode();
            //go to max down
            while (true) {
                if (val < mid->value) {
                    while (mid->leftOnLvl != nullptr) {
                        mid = mid->leftOnLvl;
                        if (val >= mid->value) break;
                    }
                    if (mid->left != nullptr) {
                        mid = mid->left;
                    } else {
                        break;
                    }
                } else {
                    while (mid->rightOnLvl != nullptr) {
                        mid = mid->rightOnLvl;
                        if (val <= mid->value) break;
                    }
                    if (mid->right != nullptr) {
                        mid = mid->right;
                    } else {
                        break;
                    }
                }
            }


            TreeNode* cur = mid->myNode;
            cur->addValueNode(val);
            if (cur->getCnt() > M) {
                rebuild(cur);
            }
        }
    }

    void rebuild(TreeNode *node) {

        if (node->past != nullptr && node->past->getCnt() < M) {
            ValueNode *valueNode = node->rebuild1();

            ValueNode *leftValueNode = valueNode->leftOnLvl;
            ValueNode *rightValueNode = valueNode->rightOnLvl;

            node->past->addValueNode(valueNode);

            TreeNode *leftNode = new TreeNode(leftValueNode->value);
            TreeNode *rightNode = new TreeNode(rightValueNode->value);

            leftNode->past = node->past;
            rightNode->past = node->past;

            leftValueNode = leftValueNode->leftOnLvl;
            rightValueNode = rightValueNode->rightOnLvl;

            while (leftValueNode != nullptr) {
                leftNode->addValueNode(leftValueNode->value);
                leftValueNode = leftValueNode->leftOnLvl;
            }

            while (rightValueNode != nullptr) {
                rightNode->addValueNode(rightValueNode->value);
                rightValueNode = rightValueNode->rightOnLvl;
            }

            node->past->left = leftNode;
            node->past->right = rightNode;

            valueNode->left->myNode = leftNode;
            valueNode->right->myNode = rightNode;

            leftNode->changeCnt(valueNode->left);
            rightNode->changeCnt(valueNode->right);


        } else {
            vector<ValueNode*> nodes = node->rebuild2();

            ValueNode *leftValueNode = nodes[0];
            ValueNode *rightValueNode = nodes[1];

            TreeNode *leftNode = new TreeNode(leftValueNode->value);
            TreeNode *rightNode = new TreeNode(rightValueNode->value);

            leftNode->past = node;
            rightNode->past = node;

            leftValueNode = leftValueNode->left;
            rightValueNode = rightValueNode->right;

            while (leftValueNode != nullptr) {
                leftNode->addValueNode(leftValueNode->value);
                leftValueNode = leftValueNode->left;
            }

            while (rightValueNode != nullptr) {
                rightNode->addValueNode(rightValueNode->value);
                rightValueNode = rightValueNode->right;
            }

//            TreeNode* past = node->past;
//            ValueNode* mid = past->getMidValueNode();
//            while (mid != nullptr){
//                if (mid->left == leftValueNode){
//                    mid->left = node->getMidValueNode();
//                    break;
//                }
//                mid = mid->leftOnLvl;
//
//            }

            node->left = leftNode;
            node->right = rightNode;

            node->getMidValueNode()->left = leftNode->getMidValueNode();
            node->getMidValueNode()->right = rightNode->getMidValueNode();

            node->left->past = node;
            node->right->past = node;

            leftNode->changeCnt(leftValueNode);
            rightNode->changeCnt(rightValueNode);
        }
    }
};