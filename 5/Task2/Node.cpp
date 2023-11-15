//
// Created by Andre on 15.11.2023.
//
#include "ValueNode.cpp"

class Node {
private:
    int cnt = 0;
    ValueNode *midValueNode = nullptr; //values into Node; Ex: Node(5, 8, 13)
    ValueNode *past = nullptr;

public:
    int getCnt() const {
        return cnt;
    }

    Node(int val) {
        midValueNode = new ValueNode(val);
        cnt++;

    }

    void addValueNode(int val) {

        ValueNode *cur = midValueNode;
        while (true) {
            if (val >= cur->value && cur->right != nullptr && val <= cur->right->value) {
                ValueNode *tmp = cur->right;

                cur->right = new ValueNode(val);
                cur->right->left = cur;
                cur->right->right = tmp;

                tmp->left = cur->right;
                break;
            }
            if (val <= cur->value && cur->left != nullptr && val >= cur->left->value) {
                ValueNode *tmp = cur->left;

                cur->left = new ValueNode(val);
                cur->left->right = cur;
                cur->left->left = tmp;

                tmp->right = cur->left;
                break;
            }

            if (val >= cur->value) {
                if (cur->right == nullptr) {
                    cur->right = new ValueNode(val);
                    cur->right->left = cur;
                    break;
                }
                cur = cur->right;
            } else {
                if (cur->left == nullptr) {
                    cur->left = new ValueNode(val);
                    cur->left->right = cur;
                    break;
                }
                cur = cur->left;
            }

        }

        cnt++;
        changeMidValueNode();
    }

    void changeMidValueNode() {
        ValueNode *cur = midValueNode;
        while (cur->left != nullptr) {
            cur = cur->left;
        }

        ValueNode *leftNode = cur;

        int k = 1;
        while (cur->right != nullptr) {
            cur = cur->right;
            k++;
        }

        for (int i = 0; i < k / 2; i++) {
            leftNode = leftNode->right;
        }

        midValueNode = leftNode;
    }

    void rebuild() {
        cnt = 1;

        ValueNode *left = midValueNode->left;
        ValueNode *right = midValueNode->right;

        left->right = nullptr;
        right->left = nullptr;


    }
};