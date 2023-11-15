//
// Created by Andre on 15.11.2023.
//

#include "Node.cpp"

class BTree {
private:
    int const M = 3;
    Node *head = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;

public:
    void add(int val) {
        if (head == nullptr) {
            head = new Node(val);
        } else {
            if (head->getCnt() < M) {
                head->addValueNode(val);
            } else {
                rebuild(*head); //тут может быть не только head, а то что надо пересобрать
            }

        }
    }

    void rebuild(Node &node) {
        node.rebuild();

        node.left = ...;
        node.right = ...;
    }
};