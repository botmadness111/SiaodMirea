//
// Created by Andre on 19.11.2023.
//

#include "TreeNode.cpp"
#include "MyObject.cpp"
#include <bits/stdc++.h>

using namespace std;

class BTree {
private:
    int const M = 3;

public:
    TreeNode *head;

    BTree() {
        head = new TreeNode();
    }

    void add(string val, string translate) {
        MyObject *object = new MyObject(val, translate);

        //go max down

        TreeNode *cur = head;

        for (int i = 0; i < cur->pointers.size(); i++) {
            string value = cur->pointers[i].val;
            if (val < value) {
                if (cur->pointers[i].next != nullptr) cur = cur->pointers[i].next;
                else break;
                i = -1;
            } else if (val > value && i == cur->pointers.size() - 1) {
                if (cur->pointers[i].next != nullptr) cur = cur->pointers[i].next;
                else break;
                i = -1;
            } else if (val > value && val < cur->pointers[i + 1].val) {
                if (cur->pointers[i].next != nullptr) cur = cur->pointers[i + 1].next;
                else break;
                i = -1;
            }
        }

        if (cur->values.size() < M) {

            if (cur->values.empty()) {
                cur->values.push_back(*object);
                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
            } else {
                cur->values.push_back(*object);
                sort(cur->values.begin(), cur->values.end());

                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
                sort(cur->pointers.begin(), cur->pointers.end());
            }


        } else {
            rebuild(cur);

            add(val, translate);
        }
    }

    void rebuild(TreeNode *cur) {

        if (cur->values.size() == M) {

            int mid = cur->values.size() / 2;
            MyObject midVal = cur->values[mid];

            //create left and right Nodes
            TreeNode *leftNode = new TreeNode();
            TreeNode *rightNode = new TreeNode();

            for (int i = 0; i < mid; i++) {
                leftNode->values.push_back(cur->values[i]);
                for (auto point: cur->pointers) {
                    if (point.val == cur->values[i].val) {
                        point.myNode = leftNode;
                        leftNode->pointers.push_back(point);
                    }
                }
            }

            for (int i = mid + 1; i < cur->values.size(); i++) {
                rightNode->values.push_back(cur->values[i]);
                for (auto point: cur->pointers) {
                    if (point.val == cur->values[i].val) {
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

                    pastNode->pointers.push_back(*new Pointer(leftNode, midVal.val, pastNode));
                    pastNode->pointers.push_back(*new Pointer(rightNode, midVal.val, pastNode));
                    sort(pastNode->pointers.begin(), pastNode->pointers.end());

                } else {
                    rebuild(pastNode);


                    //тут все переписать! PASTnODE ƒЋя left и дл€ right!!!
                    pastNode = findNode(pastNode->values[pastNode->values.size() / 2].val);

                    if (midVal.val < pastNode->values[pastNode->values.size() / 2].val) {
                        for (auto point: pastNode->pointers) {
                            if (point.val == pastNode->values[pastNode->values.size() / 2].val) {
                                pastNode = point.next;
                                break;
                            }
                        }
                    } else {
                        for (auto point: pastNode->pointers) {
                            if (point.val == pastNode->values[pastNode->values.size() / 2].val) {
                                pastNode = point.next;
                            }
                        }
                    }


                    // add midVal into past Node
                    pastNode->values.push_back(midVal);
                    sort(pastNode->values.begin(), pastNode->values.end());

                    pastNode->pointers.push_back(*new Pointer(leftNode, midVal.val, pastNode));
                    pastNode->pointers.push_back(*new Pointer(rightNode, midVal.val, pastNode));
                    sort(pastNode->pointers.begin(), pastNode->pointers.end());

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
                head->pointers.push_back(*new Pointer(leftNode, midVal.val, head));
                head->pointers.push_back(*new Pointer(rightNode, midVal.val, head));

                int k = 0;
                for (auto point: cur->pointers) {
                    if (point.val == midVal.val) {
                        if (k == 0) {
                            point.myNode = leftNode;
                            //point.val = leftNode->pointers[leftNode->pointers.size() - 1].val;
                            leftNode->pointers.push_back(point);
                        } else {
                            point.myNode = rightNode;
                            //point.val = rightNode->pointers[rightNode->pointers.size() - 1].val;
                            rightNode->pointers.push_back(point);
                        }
                        k++;
                    }
                }

                leftNode->past = head;
                rightNode->past = head;

            }
        }
    }

    TreeNode *findPastNode(string val) {
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
                if (val == value.val) return pastCur;
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

    TreeNode *findNode(string val) {
        queue<TreeNode *> myQueue;
        myQueue.push(head);


        while (!myQueue.empty()) {
            TreeNode *cur = myQueue.front();
            myQueue.pop();

            for (auto value: cur->values) {
                if (val == value.val) return cur;
            }

            for (auto point: cur->pointers) {
                if (point.next != nullptr) {
                    myQueue.push(point.next);
                }

            }
        }

        return nullptr;
    }

    string get(string val) {

        TreeNode *cur = head;

        bool flag = true;
        for (int i = 0; i < cur->pointers.size(); i++) {
            if (flag) {
                for (const auto &obj: cur->values) {
                    if (val == obj.val) return obj.translate;
                    flag = false;
                }
            }


            string value = cur->pointers[i].val;
            if (val < value) {
                if (cur->pointers[i].next != nullptr) cur = cur->pointers[i].next;
                else break;
                i = -1;
                flag = true;
            } else if (val > value && i == cur->pointers.size() - 1) {
                if (cur->pointers[i].next != nullptr) cur = cur->pointers[i].next;
                else break;
                i = -1;
                flag = true;
            } else if (val > value && val < cur->pointers[i + 1].val) {
                if (cur->pointers[i].next != nullptr) cur = cur->pointers[i + 1].next;
                else break;
                i = -1;
                flag = true;
            }
        }


        return "Not Found";
    }

    void remove(string val) {
        BTree *tree = new BTree();

        queue<TreeNode> myQueue;
        myQueue.push(*head);

        while (!myQueue.empty()) {
            TreeNode node = myQueue.front();
            myQueue.pop();

            for (auto value: node.values) {
                if (value.val != val) tree->add(value.val, value.translate);
            }

            for (auto point: node.pointers) {
                if (point.next != nullptr) myQueue.push(*point.next);
            }

        }

        this->head = tree->head;
    }


    void printTree() {
        if (head == nullptr) return;

        queue<TreeNode> myQueue;
        myQueue.push(*head);
        int enter = 1;
        int cnt = 0;

        queue<TreeNode> member;
        while (!myQueue.empty()) {
            TreeNode node = myQueue.front();
            myQueue.pop();
            member.push(node);

            cout << "[ ";
            for (auto val: node.values) {
                cout << val.val << " ";
            }
            cout << "]";

            cnt++;
            if (cnt == enter) {
                cout << endl;
                cnt = 0;
                enter = 0;

                while (!member.empty()) {
                    TreeNode nodeTmp = member.front();
                    member.pop();
                    for (auto point: nodeTmp.pointers) {
                        if (point.next != nullptr) {
                            myQueue.push(*point.next);
                            enter++;
                        }
                    }
                }
            }
        }

    }

};