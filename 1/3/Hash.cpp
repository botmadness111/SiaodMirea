//
// Created by Andre on 08.10.2023.
//

#include "iostream"
#include "HashTable.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    


    HashTable map = *new HashTable();
    string key = "���";
    string val = "Olya";
    map.put(key, val);
    //map.remove(key);

    key = "���";
    val = "lyaO";
    map.put(key, val);
    //cout << map.get(key) << endl;

    key = "����";
    val = "Kolya";
    map.put(key, val);

    key = "����";
    val = "Sanya";
    map.put(key, val);

    key = "����";
    val = "Egor";
    map.put(key, val);

    key = "����";
    val = "Vasya";
    map.put(key, val);

    key = "������";
    val = "Andrey";
    map.put(key, val);

    cout << "------------" << endl;
    key = "����";
    map.remove(key);
    key = "���";
    map.remove(key);
    map.print();


    return 0;
}