//
// Created by Andre on 24.09.2023.
//

#include <iostream>
#include <fstream>
#include <ostream>
#include <random>
#include <chrono>

using namespace std;


bool find(string nameFile, int number) {
    struct book {
        char nameCompany[14];
        int regNum;
    };

    // считывание с файла
    ifstream readFile(nameFile + ".bin", ios::binary);
    book X;

    //readFile.read((char *) &X, sizeof(book));
    while (!readFile.eof()) {
        readFile.read((char *) &X, sizeof(book));
        int num = X.regNum;
        //cout << num << endl;
        if (num == number){
            return true;
        }
    }
    readFile.close();
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Начало измерения времени
    auto startTime = std::chrono::high_resolution_clock::now();

    bool isFind = find("file", 1000990);
    cout << isFind << endl;

    // Конец измерения времени
    auto endTime = std::chrono::high_resolution_clock::now();

    // Вычисление длительности выполнения программы в миллисекундах
    auto duration = std::chrono::duration_cast<std::chrono::microseconds >(endTime - startTime);

    // Вывод длительности выполнения программы
    std::cout << "Время выполнения: " << duration.count() << " микроС" << std::endl;

    return 0;
}