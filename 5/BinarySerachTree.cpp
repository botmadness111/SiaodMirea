//
// Created by Andre on 12.11.2023.
//

#include <iostream>
#include "Node.cpp"

using namespace std;

class BinarySearchTree {
    int const STEP = 15;

public:
    struct book {
        char eng[15];
        char rus[15];
    };


private:
    int offset = 0;
    Node *head;

public:
    BinarySearchTree() {
        head = nullptr;
    };

    bool add(string name) {
        return addBinary(name);
    }

    Node get(string name) {
        return getBinary(name);
    }

    bool remove(string name) {
        return removeBinary(name);
    }

private:
    int getOffset() {
        offset += STEP;
        return offset - STEP;
    }

    bool addBinary(string &name) {
        if (head == nullptr) {
            head = new Node(name, getOffset());
            return true;
        } else {
            Node *current = head;
            while (true) {
                if (name > current->key) {
                    if (current->right == nullptr) {
                        current->right = new Node(name, getOffset());
                        current->right->past = current;
                        return true;
                    } else if (name <= current->right->key) {
                        Node *tmp = current->right;
                        current->right = new Node(name, getOffset());
                        current->right->right = tmp;
                        current->right->right->past = current->right;
                        return true;
                    } else {
                        current = current->right;
                    }
                } else if (name < current->key) {
                    if (current->left == nullptr) {
                        current->left = new Node(name, getOffset());
                        current->left->past = current->left;
                        return true;
                    } else if (name >= current->left->key) {
                        Node *tmp = current->left;
                        current->left = new Node(name, getOffset());
                        current->left->left = tmp;
                        current->left->left = current->left->past;
                        return true;
                    } else {
                        current = current->left;
                    }
                }
            }

        }
    }

    Node getBinary(string &name) {
        Node *current = head;
        while (current != nullptr) {
            if (name > current->key) {
                current = current->right;
            } else if (name < current->key) {
                current = current->left;
            } else return *current;
        }
        Node *tmp = nullptr;
        return *tmp;
    }

    bool removeBinary(string &name) {
        Node *current = head;
        while (current != nullptr) {
            if (name > current->key) {
                current = current->right;
            } else if (name < current->key) {
                current = current->left;
            } else {
                if (current == head) {
                    head = nullptr;
                    return true;
                }

                if (current == current->past->right) {
                    Node *tmp = current->right;
                    current->past->right = current->left;
                    while (current->right != nullptr) {
                        current = current->right;
                    }
                    current->right = tmp;
                } else {
                    Node *tmp = current->right;
                    current->past->left = current->right;
                    while (current->left != nullptr) {
                        current = current->left;
                    }
                    current->left = tmp;
                }

                return true;

            }
        }
        return false;

    }

};
