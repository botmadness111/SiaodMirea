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

        bool flag = true;
        while (flag) {
            flag = false;
            int i = 0;
            for (i = 0; i < cur->values.size(); i++) {
                string value = cur->values[i].val;
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
                cur->values.push_back(*object);
                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
            } else {
                cur->values.push_back(*object);
                sort(cur->values.begin(), cur->values.end());

                cur->pointers.push_back(*new Pointer(nullptr, val, cur));
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

                } else {
                    rebuild(pastNode);

                    pastNode = findPastNode(midVal.val);
                    cur->past = pastNode;

                    // add midVal into past Node
                    pastNode->values.push_back(midVal);
                    sort(pastNode->values.begin(), pastNode->values.end());

                    pastNode->pointers.push_back(*new Pointer(leftNode, midVal.val, pastNode));
                    pastNode->pointers.push_back(*new Pointer(rightNode, midVal.val, pastNode));

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
                for (auto point: cur->pointers){
                    if (point.val == midVal.val){
                        pastNode->pointers.push_back(point);
                    }
                }

                leftNode->past = head;
                rightNode->past = head;

            }

            //delete midVal of pointers of Current Node
//            std::vector<Pointer> pointers;
//            for (auto point: cur->pointers) {
//                if (point.val != midVal.val) {
//                    point.myNode = cur;
//                    pointers.push_back(point);
//                }
//            }
//
//            cur->pointers.clear();
//            for (auto point: pointers) {
//                cur->pointers.push_back(point);
//            }
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

    string get(string val) {

        TreeNode *cur = head;

        bool flag = true;
        while (flag) {

            for (auto value: cur->values) {
                if (value.val == val) return value.translate;
            }

            flag = false;
            int i = 0;
            for (i = 0; i < cur->values.size(); i++) {
                string value = cur->values[i].val;
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
                if (value.val == "l"){
                    cout << 123 << endl;
                }
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
        int enter = head->values.size();
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