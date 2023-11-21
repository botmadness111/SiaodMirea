//
// Created by Andre on 24.11.2023.
//
#include <iostream>
#pragma once

using namespace std;

class MyObject {
public:
    string val;
    string translate;

    MyObject(string val, string translate) {
        this->val = std::move(val);
        this->translate = std::move(translate);
    }

    MyObject() {}

    // Перегрузка оператора < для сравнения объектов
    bool operator<(const MyObject& other) const {
        return val < other.val;
    }
};