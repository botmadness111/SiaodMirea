//
// Created by Andre on 19.11.2023.
//

#include "vector"
#include "Pointer.cpp"
#include "MyObject.cpp"

using namespace std;

class TreeNode {
public:
    std::vector<MyObject> values;
    std::vector<Pointer> pointers;
    TreeNode *past = nullptr;

    TreeNode() {
    }

};
