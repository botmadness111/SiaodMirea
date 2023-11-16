//
// Created by Andre on 15.11.2023.
//


#include "ValueNode.cpp"
#include "vector"

using namespace std;

class TreeNode {
private:
    int cnt = 0;
    ValueNode *midValueNode = nullptr; //values into Node; Ex: Node(5, 8, 13)


public:
    TreeNode *past = nullptr;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    ValueNode *getMidValueNode() const {
        return midValueNode;
    }

    TreeNode(int val) {
        midValueNode = new ValueNode(val, this);
        cnt++;
    }

    TreeNode(){}

    int getCnt() const {
        return cnt;
    }

    void addValueNode(int val) {

        ValueNode *cur = midValueNode;
        while (true) {
            if (val >= cur->value && cur->rightOnLvl != nullptr && val <= cur->rightOnLvl->value) {
                ValueNode *tmp = cur->rightOnLvl;

                ValueNode *newValueNode = new ValueNode(val, this);

                cur->right = newValueNode;
                cur->rightOnLvl = newValueNode;

                cur->right->left = cur;
                cur->right->leftOnLvl = cur;
                cur->right->right = tmp;
                cur->right->rightOnLvl = tmp;

                tmp->left = cur->right;
                tmp->leftOnLvl = cur->right;
                break;
            }
            if (val <= cur->value && cur->leftOnLvl != nullptr && val >= cur->leftOnLvl->value) {
                cout << val << endl;
                ValueNode *tmp = cur->leftOnLvl;

                ValueNode *newValueNode = new ValueNode(val, this);

                cur->left = newValueNode;
                cur->leftOnLvl = newValueNode;
                newValueNode->right = cur;
                newValueNode->rightOnLvl = cur;
                newValueNode->left = tmp;
                newValueNode->leftOnLvl = tmp;

                tmp->right = newValueNode;
                tmp->rightOnLvl = newValueNode;
                break;
            }

            if (val >= cur->value) {
                if (cur->rightOnLvl == nullptr) {
                    ValueNode *newValueNode = new ValueNode(val, this);
                    cur->right = newValueNode;
                    cur->right->left = cur;

                    cur->rightOnLvl = newValueNode;
                    cur->right->leftOnLvl = cur;

                    break;
                }
                cur = cur->right;
            } else {
                if (cur->leftOnLvl == nullptr) {

                    ValueNode *newValueNode = new ValueNode(val, this);

                    cur->left = newValueNode;
                    cur->left->right = cur;

                    cur->leftOnLvl = newValueNode;
                    cur->left->rightOnLvl = cur;

                    break;
                }
                cur = cur->left;
            }

        }

        cnt++;
        changeMidValueNode(cur);
        changeCnt(cur);
    }

    void addValueNode(ValueNode *valueNode) {

        int val = valueNode->value;
        ValueNode *cur = midValueNode;
        while (true) {
            if (val >= cur->value && cur->rightOnLvl != nullptr && val <= cur->rightOnLvl->value) {
                ValueNode *tmp = cur->rightOnLvl;

                cur->rightOnLvl = valueNode;
                valueNode->rightOnLvl = tmp;
                valueNode->leftOnLvl = cur;

                tmp->leftOnLvl = valueNode;

                valueNode->myNode = this;
                break;
            }
            if (val <= cur->value && cur->leftOnLvl != nullptr && val >= cur->leftOnLvl->value) {
                ValueNode *tmp = cur->leftOnLvl;

                cur->leftOnLvl = valueNode;
                valueNode->leftOnLvl = tmp;
                valueNode->rightOnLvl = cur;

                tmp->rightOnLvl = valueNode;

                valueNode->myNode = this;
                break;
            }

            if (val >= cur->value) {
                if (cur->rightOnLvl == nullptr) {
                    valueNode->rightOnLvl = cur->rightOnLvl;
                    cur->rightOnLvl = valueNode;
                    valueNode->leftOnLvl = cur;

                    valueNode->myNode = this;
                    break;
                }
                cur = cur->rightOnLvl;
            } else {
                if (cur->leftOnLvl == nullptr) {
                    valueNode->leftOnLvl = cur->leftOnLvl;
                    cur->leftOnLvl = valueNode;
                    valueNode->rightOnLvl = cur;

                    valueNode->myNode = this;
                    break;
                }
                cur = cur->leftOnLvl;
            }

        }

        cnt++;
        changeMidValueNode(cur);
        changeCnt(cur);
    }

    void changeMidValueNode(ValueNode *cur) {
        while (cur->leftOnLvl != nullptr) {
            cur = cur->leftOnLvl;
        }

        ValueNode *leftNode = cur;

        int k = 1;
        while (cur->rightOnLvl != nullptr) {
            cur = cur->rightOnLvl;
            k++;
        }

        for (int i = 0; i < k / 2; i++) {
            leftNode = leftNode->rightOnLvl;
        }

        midValueNode = leftNode;
    }

    void changeCnt(ValueNode *cur) {
        if (cur == nullptr) return;

        TreeNode *myNode = cur->myNode;

        while (cur->leftOnLvl != nullptr) {
            cur = cur->leftOnLvl;
        }

        int k = 0;
        while (cur != nullptr) {
            cur = cur->rightOnLvl;
            k++;
        }
        myNode->cnt = k;
    }

    vector<ValueNode *> rebuild2() {
        cnt = 1;

        ValueNode *leftValueNode = midValueNode->left;
        ValueNode *rightValueNode = midValueNode->right;

        if (leftValueNode != nullptr) leftValueNode->right = nullptr;
        if (leftValueNode != nullptr) leftValueNode->rightOnLvl = nullptr;
        if (rightValueNode != nullptr) rightValueNode->left = nullptr;
        if (rightValueNode != nullptr) rightValueNode->leftOnLvl = nullptr;

        midValueNode->left = nullptr;
        midValueNode->leftOnLvl = nullptr;
        midValueNode->right = nullptr;
        midValueNode->rightOnLvl = nullptr;

        std::vector<ValueNode *> nodes;
        nodes.push_back(leftValueNode);
        nodes.push_back(rightValueNode);

        changeCnt(leftValueNode);
        changeCnt(rightValueNode);
        return nodes;
    }

    ValueNode *rebuild1() {
        cnt--;

        ValueNode *mid = midValueNode;

        ValueNode *leftValueNode = midValueNode->left;
        ValueNode *rightValueNode = midValueNode->right;

        if (leftValueNode != nullptr) {
            leftValueNode->right = nullptr;
            leftValueNode->rightOnLvl = nullptr;
        }


        if (rightValueNode != nullptr) {
            rightValueNode->left = nullptr;
            rightValueNode->leftOnLvl = nullptr;
        }

        if (leftValueNode != nullptr)
            changeMidValueNode(leftValueNode);
        if (rightValueNode != nullptr)
            changeMidValueNode(rightValueNode);


        changeCnt(leftValueNode);
        changeCnt(rightValueNode);
        return mid;
    }
};