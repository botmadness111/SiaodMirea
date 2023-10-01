//
// Created by Andre on 24.09.2023.
//

#include <iostream>
#include <fstream>
#include <ostream>
#include <random>
#include <sstream>
#include <chrono>
#include <windows.h>

using namespace std;


bool find(string nameFile, int number) {
    struct book {
        char nameCompany[14];
        int regNum;
    };

//    //Запись числа в бинарном виде
//    ofstream writeFileTmp1("tmp.bin", ios::trunc);
//    writeFileTmp1.close();
//    ofstream writeFileTmp("tmp.bin", ios::in | ios::binary | ios::app);
//    writeFileTmp.write((char *) &number, sizeof(int));
//    writeFileTmp.close();
//
//    // считывание бинарного числа в char[6]
//    char symbols[6];
//    ifstream readFileTmp("tmp.bin", ios::binary | ios::in);
//    string numberBin;
//    getline(readFileTmp, numberBin);
//    readFileTmp.close();

//    int i = 0;
//    for (auto bit: numberBin) {
//        symbols[i] = bit;
//        i++;
//    }

    // считывание с файла
    ifstream readFile(nameFile + ".bin", ios::in);
    book X;
    while (!readFile.eof()) {
        readFile.read((char *) &X, sizeof(book));

        int num = X.regNum;
        if (num == number){
            return true;
        }

        //string line;
        //getline(readFile, line);

        //if (line.empty()) break;

        //Считвание с бинарного файла string[name, regNum]
        //---------------------------------------------------------
//        string array[2];
//        stringstream ss(line);
//        string token;
//
//        if (line.size() < 20) continue;
//        token = line.substr(0, 14);
//        array[0] = token;
//        token = line.substr(16, 21);
//        array[1] = token;



        //---------------------------------------------------------

        //считывание бинарного числа в char[6]
        //string regNum = array[1];
        //cout << regNum << " ";


//        char regNumBin[6];
//        i = 0;
//        for (auto bit: regNum) {
//            regNumBin[i] = bit;
//            i++;
//        }

//        bool flag = true;
//        for (i = 0; i < 6; i++) {
//            if (symbols[i] != regNumBin[i]) {
//                flag = false;
//                break;
//            }
//        }
//        if (flag) {
//            return true;
//        }
        //cout << 222 << endl;
    }
    readFile.close();
    //cout << cnt << endl;
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Начало измерения времени
    auto startTime = std::chrono::high_resolution_clock::now();

    bool isFind = find("file", 125734);
    cout << isFind << endl;

    // Конец измерения времени
    auto endTime = std::chrono::high_resolution_clock::now();

    // Вычисление длительности выполнения программы в миллисекундах
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Вывод длительности выполнения программы
    std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;

    return 0;
}