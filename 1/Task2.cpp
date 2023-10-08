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

    // ���������� � �����
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

    // ������ ��������� �������
    auto startTime = std::chrono::high_resolution_clock::now();

    bool isFind = find("file", 1000990);
    cout << isFind << endl;

    // ����� ��������� �������
    auto endTime = std::chrono::high_resolution_clock::now();

    // ���������� ������������ ���������� ��������� � �������������
    auto duration = std::chrono::duration_cast<std::chrono::microseconds >(endTime - startTime);

    // ����� ������������ ���������� ���������
    std::cout << "����� ����������: " << duration.count() << " ������" << std::endl;

    return 0;
}