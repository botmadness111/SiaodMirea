//
// Created by Andre on 08.10.2023.
//

#include "iostream"
#include "HashTable.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    


    HashTable map = *new HashTable();
    string key = "Оля";
    string val = "Olya";
    map.put(key, val);
    //map.remove(key);

    key = "ляО";
    val = "lyaO";
    map.put(key, val);
    //cout << map.get(key) << endl;

    key = "Коля";
    val = "Kolya";
    map.put(key, val);

    key = "Саня";
    val = "Sanya";
    map.put(key, val);

    key = "Егор";
    val = "Egor";
    map.put(key, val);

    key = "Вася";
    val = "Vasya";
    map.put(key, val);

    key = "Андрей";
    val = "Andrey";
    map.put(key, val);

    cout << "------------" << endl;
    key = "Вася";
    map.remove(key);
    key = "ляО";
    map.remove(key);
    map.print();


    return 0;
}