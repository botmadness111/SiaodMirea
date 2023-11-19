//
// Created by Andre on 19.11.2023.
//

#include "vector"
#include "Pointer.cpp"

class TreeNode {
public:
    std::vector<int> values;
    std::vector<Pointer> pointers;
    TreeNode *past = nullptr;

    TreeNode() {
    }

};
