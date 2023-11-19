//
// Created by Andre on 19.11.2023.
//

#include "TreeNode.cpp"
#include <bits/stdc++.h>

using namespace std;

class BTree {
private:
    int const M = 3;
    TreeNode *head;

public:

    BTree() {
        head = new TreeNode();
    }

    void add(int val) {
        //go max down

        TreeNode *cur = head;
        for (auto value: cur->values) {
            if (val <= value) {
                //take point of value
                for (auto point: cur->pointers) {
                    if (point.val == value && point.next != nullptr) {
                        cur = point.next;
                        break;
                    }
                }
            }
        }

        if (cur->values.size() < M) {

            if (cur->values.empty()) {
                cur->values.push_back(val);
                cur->pointers.push_back(*new Pointer(nullptr, val));
                cur->pointers.push_back(*new Pointer(nullptr, val));
            } else {
                cur->values.push_back(val);
                sort(cur->values.begin(), cur->values.end());

                cur->pointers.push_back(*new Pointer(nullptr, val));
            }


        } else {
            rebuild();

            add(val);

        }
    }

    void rebuild() {
        TreeNode *cur = head;

        if (cur->values.size() == M) {
            int mid = cur->values.size() / 2;
            int midVal = cur->values[mid];

            //delete midVal of pointers of Current Node
            std::vector<Pointer> pointers;
            for (auto point: cur->pointers) {
                if (point.val != midVal) {
                    pointers.push_back(point);
                }
            }

            cur->pointers.clear();
            for (auto point: pointers) {
                cur->pointers.push_back(point);
            }

            //create left and right Nodes
            TreeNode *leftNode = new TreeNode();
            TreeNode *rightNode = new TreeNode();

            for (int i = 0; i < mid; i++) {
                leftNode->values.push_back(cur->values[i]);
                for (auto point: cur->pointers) {
                    if (point.val == cur->values[i]) {
                        leftNode->pointers.push_back(point);
                    }
                }
            }

            for (int i = mid + 1; i < cur->values.size(); i++) {
                rightNode->values.push_back(cur->values[i]);
                for (auto point: cur->pointers) {
                    if (point.val == cur->values[i]) {
                        rightNode->pointers.push_back(point);
                    }
                }
            }

            TreeNode *pastNode = cur->past;
            if (pastNode != nullptr) {
                //delete Nodes for empty pointers
                std::vector<Pointer> pointersPast;
                for (auto point: pastNode->pointers) {
                    if (point.next != cur) {
                        pointersPast.push_back(point);
                    }
                }

                pastNode->pointers.clear();
                for (auto point: pointersPast) {
                    pastNode->pointers.push_back(point);
                }

                // add midVal into past Node
                if (pastNode->values.size() < M) {
                    pastNode->values.push_back(midVal);
                    sort(pastNode->values.begin(), pastNode->values.end());

                    pastNode->pointers.push_back(*new Pointer(leftNode, midVal));
                    pastNode->pointers.push_back(*new Pointer(rightNode, midVal));

                }
            } else {
                head = new TreeNode();
                head->values.push_back(midVal);
                head->pointers.push_back(*new Pointer(leftNode, midVal));
                head->pointers.push_back(*new Pointer(rightNode, midVal));
            }
        }
    }
};