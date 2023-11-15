//
// Created by Andre on 15.11.2023.
//

class ValueNode {
public:
    int value;
    ValueNode *head = nullptr; // its mid
    ValueNode *right = nullptr;
    ValueNode *left = nullptr;
    ValueNode *past = nullptr;

    ValueNode(){}

    ValueNode(int val) {
        this->value = val;
    }

};
