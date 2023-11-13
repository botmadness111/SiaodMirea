
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "iostream"
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

class Tree {
    int val = 0;
    Tree *left = nullptr;
    Tree *right = nullptr;
    int deep = -1;
    int size = 1;
    int cntChildrens = 0;
    int lvl = 0;
public:

    Tree(int val) {
        this->val = val;
    }

    void add(int val) {
        Tree *mainHead = this;
        Tree *head = this;

        while (true) {
            if (val < head->val) {
                Tree *left = head->left;

                if (left != nullptr) {
                    if (val < left->val) {
                        head = left;
                    } else {
                        Tree *newNode = new Tree(val);

                        Tree *leftTmp = head->left;
                        head->left = newNode;
                        newNode->left = leftTmp;

                        break;
                    }
                } else {
                    Tree *newNode = new Tree(val);
                    head->left = newNode;
                    break;
                }
            } else {
                Tree *right = head->right;

                if (right != nullptr) {
                    if (val >= right->val) {
                        head = right;
                    } else {
                        Tree *newNode = new Tree(val);

                        Tree *rightTmp = head->right;
                        head->right = newNode;
                        newNode->right = rightTmp;

                        break;
                    }
                } else {
                    Tree *newNode = new Tree(val);
                    head->right = newNode;
                    break;
                }
            }
        }
        size++;
        updateDeep(mainHead); //After add -> update deep every node
        rebuild(); //After add -> rebuild every node
    }

    int updateDeep(Tree *&root) {
        if (root == nullptr) return -1;

        int left = updateDeep(root->left);
        int right = updateDeep(root->right);

        root->deep = max(left, right) + 1;
        return root->deep;
    }

    bool isBalance(Tree *node) {
        int left = -1;
        int right = -1;
        if (node->left != nullptr) left = node->left->deep;
        if (node->right != nullptr) right = node->right->deep;

        if (abs(left - right) > 1) {
            return false;
        }
        return true;
    }

    void getValues(Tree *node, vector<int> &values) {
        if (node == nullptr) return;

        getValues(node->left, values);
        values.push_back(node->val);
        getValues(node->right, values);

    }

    int getMedianIndex(vector<int> &values) {
        return values.size() / 2;
    }

    void helperRebuildAdd(int val) {
        Tree *head = this;
        while (true) {
            if (val < head->val) {
                Tree *left = head->left;

                if (left != nullptr) {
                    if (val < left->val) {
                        head = left;
                    } else {
                        Tree *newNode = new Tree(val);

                        Tree *leftTmp = head->left;
                        head->left = newNode;
                        newNode->left = leftTmp;

                        break;
                    }
                } else {
                    Tree *newNode = new Tree(val);
                    head->left = newNode;
                    break;
                }
            } else {
                Tree *right = head->right;

                if (right != nullptr) {
                    if (val >= right->val) {
                        head = right;
                    } else {
                        Tree *newNode = new Tree(val);

                        Tree *rightTmp = head->right;
                        head->right = newNode;
                        newNode->right = rightTmp;

                        break;
                    }
                } else {
                    Tree *newNode = new Tree(val);
                    head->right = newNode;
                    break;
                }
            }
        }
    }

    void rebuild() {
        Tree *head = this;

        queue<Tree *> qu;
        qu.push(head);
        while (!qu.empty()) {
            head = qu.front();
            qu.pop();
            if (!isBalance(head)) {

                vector<int> values;
                getValues(head, values);
                int medianIndex = getMedianIndex(values);
                int median = values[medianIndex];

                head->val = median;
                head->left = nullptr;
                head->right = nullptr;

                for (int i = 0; i < values.size(); i++) {
                    if (i != medianIndex) {
                        head->helperRebuildAdd(values[i]);
                    }
                }
            }
            Tree *left = head->left;
            Tree *right = head->right;

            if (left != nullptr) qu.push(left);
            if (right != nullptr) qu.push(right);
        }
    }

    void removeLastLeft() {
        Tree *head = this;
        if (head->left == nullptr) return;

        while (head->left->left != nullptr) head = head->left;

        head->left = nullptr;


        rebuild();
    }

    int getCountChildrensHelper(Tree *node) {
        if (node == nullptr) return 0;

        int left = getCountChildrensHelper(node->left);
        int right = getCountChildrensHelper(node->right);
        node->cntChildrens = left + right;

        return left + right + 1;
    }

    vector<int> getCountChildrens() {
        Tree *node = this;
        getCountChildrensHelper(node);

        queue<Tree *> qu;
        node = this;
        qu.push(node);

        vector<int> array;

        while (!qu.empty()) {
            node = qu.front();
            qu.pop();

            int cnt = node->cntChildrens;
            array.push_back(cnt);

            Tree *left = nullptr;
            Tree *right = nullptr;

            if (node->left != nullptr) left = node->left;
            if (node->right != nullptr) right = node->right;

            if (left != nullptr) qu.push(left);
            if (right != nullptr) qu.push(right);
        }
        return array;
    }

    void getLvlNodeHelper(Tree *node, int lvl) {
        if (node == nullptr) return;

        getLvlNodeHelper(node->left, lvl + 1);
        getLvlNodeHelper(node->right, lvl + 1);

        node->lvl = lvl;
    }

    vector<int> getLvlNode() {
        Tree *node = this;
        getLvlNodeHelper(node, node->lvl);

        queue<Tree *> qu;
        node = this;
        qu.push(node);

        vector<int> array;

        while (!qu.empty()) {
            node = qu.front();
            qu.pop();

            array.push_back(node->lvl);

            Tree *left = nullptr;
            Tree *right = nullptr;

            if (node->left != nullptr) left = node->left;
            if (node->right != nullptr) right = node->right;

            if (left != nullptr) qu.push(left);
            if (right != nullptr) qu.push(right);
        }
        return array;
    }

    void print() {
        queue<Tree *> qu;
        Tree *head = this;
        qu.push(head);

        while (!qu.empty()) {
            Tree *node = qu.front();
            qu.pop();

            cout << node->val << " ";

            Tree *left = nullptr;
            Tree *right = nullptr;

            if (node->left != nullptr) left = node->left;
            if (node->right != nullptr) right = node->right;

            if (left != nullptr) qu.push(left);
            if (right != nullptr) qu.push(right);
        }
    }


};