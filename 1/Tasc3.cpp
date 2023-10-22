#include <iostream>
#include <fstream>
#include <ostream>
#include <random>
#include <chrono>


using namespace std;

struct book {
    char nameCompany[14];
    int regNum;
};

struct bangBang {
    int regNum;
    int offset;
};

vector<bangBang> createMap(string nameFile) {
    // считывание с файла
    ifstream readFile(nameFile + ".bin", ios::binary);
    vector<bangBang> array;
    book X;
    int i = 0;
    while (!readFile.eof()) {
        readFile.read((char *) &X, sizeof(book));

        char name[14];
        int index = 0;
        for (auto chr: X.nameCompany) {
            name[index] = chr;
            index++;
        }

        int number = X.regNum;

        bangBang Y;
        Y.regNum = number;
        Y.offset = i * sizeof(book);

        array.push_back(Y);

        i++;
    }
    readFile.close();
    return array;
}


int binaryFind(vector<bangBang> arraySorted, int find) {


    int right = arraySorted.size() - 1;
    int left = 0;

    while (arraySorted[left].regNum <= find && arraySorted[right].regNum >= find && left <= right) {

        if (arraySorted[left].regNum == arraySorted[right].regNum) break; // зашита от деления на 0

        int mid = left + ((find - arraySorted[left].regNum) * (right - left)) /
                         (arraySorted[right].regNum - arraySorted[left].regNum);

        if (arraySorted[mid].regNum == find) return arraySorted[mid].offset;

        if (arraySorted[mid].regNum > find) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

string getName(string nameFile, int offset) {
    string result = "";

    book X;
    ifstream readFile(nameFile + ".bin", ios::binary);
    readFile.seekg(offset);
    readFile.read((char *) &X, sizeof(book));
    for (auto chr: X.nameCompany){
        result += chr;
    }
    readFile.close();
    return result;
}


int main() {
    setlocale(LC_ALL, "Russian");

    vector<bangBang> array = createMap("file");

    // Начало измерения времени
    auto startTime = std::chrono::high_resolution_clock::now();

    int offset = binaryFind(array, 1000572);
    cout << offset << endl;

    // Конец измерения времени
    auto endTime = std::chrono::high_resolution_clock::now();

    // Вычисление длительности выполнения программы в миллисекундах
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    // Вывод длительности выполнения программы
    std::cout << "time  " << duration.count() << " micros" << std::endl;

    cout << getName("file", offset);

    return 0;
}
