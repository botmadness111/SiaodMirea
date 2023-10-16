//
// Created by Andre on 08.10.2023.
//

#include "iostream"
#include "HashTable.cpp"
#include <ostream>
#include <fstream>
#include <chrono>

using namespace std;

void updateToBinaryFile() {
    setlocale(LC_ALL, "Russian");
    string nameFile = "base";

    ifstream readFile(nameFile + ".txt", ios::in);

    ofstream writeFile1(nameFile + ".bin", ios::trunc);
    writeFile1.close();

    ofstream writeFile(nameFile + ".bin", ios::in | ios::binary | ios::app);

    if (!readFile.is_open()) {
        cout << "No open file: " << nameFile << ".txt";
        return;
    }

    if (!writeFile) {
        cout << "No open file: " << nameFile << ".bin";
        return;
    }
    while (!readFile.eof()) {
        setlocale(LC_ALL, "Russian");
        string record;
        getline(readFile, record);

        //---------------------------------------------------------

        if (record.empty()) continue;

//        cout << record << endl;


        writeFile.write((char *) &record, sizeof(record));


    }

    readFile.close();
    writeFile.close();
}


int main() {


    updateToBinaryFile();

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

    // Начало измерения времени
    auto startTime = std::chrono::high_resolution_clock::now();

    map.put(key, val);

    // Конец измерения времени
    auto endTime = std::chrono::high_resolution_clock::now();
    // Вычисление длительности выполнения программы в миллисекундах
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    // Вывод длительности выполнения программы
    std::cout << "Время выполнения: " << duration.count() << " микроС" << std::endl;

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


    startTime = std::chrono::high_resolution_clock::now();

    map.remove(key);
    key = "ляО";
    map.remove(key);

    // Конец измерения времени
    endTime = std::chrono::high_resolution_clock::now();
    // Вычисление длительности выполнения программы в миллисекундах
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    // Вывод длительности выполнения программы
    std::cout << "Время выполнения: " << duration.count() << " микроС" << std::endl;

    map.print();


    return 0;
}