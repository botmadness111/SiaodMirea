//
// Created by Andre on 08.10.2023.
//

#include <chrono>
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


    key = "����";
    auto startTime = std::chrono::high_resolution_clock::now();
    map.get(key);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    key = "���";
    startTime = std::chrono::high_resolution_clock::now();
    map.get(key);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    key = "������";
    startTime = std::chrono::high_resolution_clock::now();
    map.get(key);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;



    cout << "------------" << endl;

    key = "���";
    startTime = std::chrono::high_resolution_clock::now();
    map.remove(key);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    key = "����";
    startTime = std::chrono::high_resolution_clock::now();
    map.remove(key);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    key = "������";
    startTime = std::chrono::high_resolution_clock::now();
    map.remove(key);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;


    return 0;
}