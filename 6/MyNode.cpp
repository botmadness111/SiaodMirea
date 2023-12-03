#include <iostream>

using namespace std;

class MyNode {

public:
    int value;
    MyNode *past;
    string key;

    MyNode(MyNode *past, string key, int value) {
        this->past = past;
        this->value = value;
        this->key = std::move(key);
    }

};