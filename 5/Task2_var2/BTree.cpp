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

        bool flag = true;
        while (flag) {
            flag = false;
            int i = 0;
            for (i = 0; i < cur->values.size(); i++) {
                int value = cur->values[i];
                if (val < value) {
                    int k = 0;
                    if (i == 0) {
                        for (auto point: cur->pointers) {
                            if (point.val == value && point.next != nullptr) {
                                cur = point.next;
                                flag = true;
                                break;
                            }
                        }
                        break;
                    } else {
                        TreeNode *firstCur = nullptr;
                        for (auto point: cur->pointers) {
                            if (point.val == value && point.next != nullptr) {
                                if (firstCur == nullptr) firstCur = point.next;
                                flag = true;
                                k++;
                            }
                        }
                        if (k == 2) {
                            cur = firstCur;
                            break;
                        }
                    }

                } else {
                    int k = 0;
                    if (i == cur->values.size() - 1) {
                        for (auto point: cur->pointers) {
                            if (point.val == value && point.next != nullptr) {
                                cur = point.next;
                                flag = true;
                            }
                        }
                        break;
                    } else {
                        TreeNode *lastCur = nullptr;
                        for (auto point: cur->pointers) {
                            if (point.val == value && point.next != nullptr) {
                                lastCur = point.next;
                                flag = true;
                                k++;
                            }
                        }
                        if (k == 2) {
                            cur = lastCur;
                            break;
                        }
                    }
                }
            }
        }

        if (cur->values.size() < M) {

            if (cur->values.empty()) {
                cur->values.push_back(val);
                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
            } else {
                cur->values.push_back(val);
                sort(cur->values.begin(), cur->values.end());

                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
            }


        } else {
            rebuild(cur);

            add(val);

        }
    }

    void rebuild(TreeNode *cur) {

        if (cur->values.size() == M) {
            int mid = cur->values.size() / 2;
            int midVal = cur->values[mid];

            //delete midVal of pointers of Current Node
            std::vector<Pointer> pointers;
            for (auto point: cur->pointers) {
                if (point.val != midVal) {
                    point.myNode = cur;
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
                        point.myNode = leftNode;
                        leftNode->pointers.push_back(point);
                    }
                }
            }

            for (int i = mid + 1; i < cur->values.size(); i++) {
                rightNode->values.push_back(cur->values[i]);
                for (auto point: cur->pointers) {
                    if (point.val == cur->values[i]) {
                        point.myNode = rightNode;
                        rightNode->pointers.push_back(point);
                    }
                }
            }

            TreeNode *pastNode = cur->past;
            if (pastNode != nullptr) {
                // add midVal into past Node
                if (pastNode->values.size() < M) {
                    pastNode->values.push_back(midVal);
                    sort(pastNode->values.begin(), pastNode->values.end());

                    pastNode->pointers.push_back(*new Pointer(leftNode, midVal, pastNode));
                    pastNode->pointers.push_back(*new Pointer(rightNode, midVal, pastNode));

                } else {
                    rebuild(pastNode);

                    //тут переписать past - он будет равен новому left/right
                    //тут нужно начать с head

                    pastNode = findPastNode(midVal);
                    cur->past = pastNode;

                    // add midVal into past Node
                    pastNode->values.push_back(midVal);
                    sort(pastNode->values.begin(), pastNode->values.end());

                    pastNode->pointers.push_back(*new Pointer(leftNode, midVal, pastNode));
                    pastNode->pointers.push_back(*new Pointer(rightNode, midVal, pastNode));


                }

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


                leftNode->past = pastNode;
                rightNode->past = pastNode;
            } else {
                head = new TreeNode();
                head->values.push_back(midVal);
                head->pointers.push_back(*new Pointer(leftNode, midVal, head));
                head->pointers.push_back(*new Pointer(rightNode, midVal, head));

                leftNode->past = head;
                rightNode->past = head;
            }
        }
    }

    TreeNode *findPastNode(int val) {
        queue<TreeNode *> myQueue;
        myQueue.push(head);

        queue<TreeNode *> myQueuePast;
        myQueuePast.push(nullptr);

        while (!myQueue.empty()) {
            TreeNode *cur = myQueue.front();
            myQueue.pop();

            TreeNode *pastCur = myQueuePast.front();
            myQueuePast.pop();

            for (auto value: cur->values) {
                if (val == value) return pastCur;
            }

            for (auto point: cur->pointers) {
                if (point.next != nullptr) {
                    myQueue.push(point.next);
                    myQueuePast.push(point.myNode);
                }

            }
        }

        return nullptr;
    }

};