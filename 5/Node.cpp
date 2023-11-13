//
// Created by Andre on 12.11.2023.
//

#include <iostream>

using namespace std;

class Node {
private:
    int offset;

public:
    string key;
    Node *past = nullptr;
    Node left = nullptr;
    Node right = nullptr;

    Node(string key, int offset) {
        this->key = key;
        this->offset = offset;
    }

    Node() {}
};