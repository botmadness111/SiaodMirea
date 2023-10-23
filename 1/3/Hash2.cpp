#include "iostream"
#include "HashTableBin.h"
#include "HashTableBin.cpp"
#include <fstream>
#include <ostream>
#include <chrono>

using namespace std;

void updateToBinaryFile(string nameFile) {

    struct book {
        char eng[15];
        char rus[15];
//        int offset;
    };

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

    int k = 0;
    while (!readFile.eof()) {
        string rus;
        string eng;
        int offset;
        getline(readFile, eng);
        getline(readFile, rus);

        //---------------------------------------------------------

        if (rus.empty()) continue;

        char rusCharArray[15];
        copy(rus.begin(), rus.begin() + 15, rusCharArray);

        if (eng.empty()) continue;

        char engCharArray[15];
        copy(eng.begin(), eng.begin() + 15, engCharArray);

        book X;
        for (int i = 0; i < 15; i++) {
            X.rus[i] = rusCharArray[i];
        }
        for (int i = 0; i < 15; i++) {
            X.eng[i] = engCharArray[i];
        }
//        X.offset = k * sizeof(book);

        writeFile.write((char *) &X, sizeof(book));

        k++;
    }

    readFile.close();
    writeFile.close();
}

void updateToHashTable(string nameFile, HashTableBin &map) {

    struct book {
        char eng[15];
        char rus[15];
//        int offset;
    };

    // ���������� � �����
    ifstream readFile(nameFile + ".bin", ios::binary);
    book X;

    int k = 0;
    while (!readFile.eof()) {
        readFile.read((char *) &X, sizeof(book));
        char *eng = X.eng;
        char *rus = X.rus;
        string rusStr = rus;
        string engStr = eng;

        int offset = k * sizeof(book);

        map.put(engStr, offset);

        k++;

    }
    readFile.close();
}


int main() {
    setlocale(LC_ALL, "Russian");
    updateToBinaryFile("base3");
    HashTableBin map = *new HashTableBin();

    //fill map
    cout << "--------------------" << endl;
    updateToHashTable("base3", map);
    map.print();

    cout << "--------------------" << endl;

    string key = "New";
    // ������ ��������� �������
    auto startTime = std::chrono::high_resolution_clock::now();
    cout << map.getByBin(key) << endl;

    // ����� ��������� �������
    auto endTime = std::chrono::high_resolution_clock::now();

    // ���������� ������������ ���������� ��������� � �������������
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    // ����� ������������ ���������� ���������
    std::cout << "time  " << duration.count() << " micros" << std::endl;


    key = "Doctor";
    // ������ ��������� �������
    startTime = std::chrono::high_resolution_clock::now();

    cout << map.getByBin(key) << endl;

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    key = "Sad";
    startTime = std::chrono::high_resolution_clock::now();

    cout << map.getByBin(key) << endl;

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    cout << "---------------------" << endl;

    key = "Sad";
    startTime = std::chrono::high_resolution_clock::now();

    map.remove(key);

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    key = "Doctor";
    startTime = std::chrono::high_resolution_clock::now();

    map.remove(key);

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    key = "New";
    startTime = std::chrono::high_resolution_clock::now();

    map.remove(key);

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "time  " << duration.count() << " micros" << std::endl;


    return 0;
}
