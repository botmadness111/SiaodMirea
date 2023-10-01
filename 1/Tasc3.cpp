#include <iostream>
#include <fstream>
#include <ostream>
#include <random>


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
    ifstream readFile(nameFile + ".bin", ios::in);
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
    return array;
}


void binaryFind(vector<bangBang> array, int find) {
    

    int right = array.size() - 1;
    int left = 0;

    int mid = left + ((find - sortedArray[left]) * (right - left)) / (sortedArray[right] - sortedArray[left]);

}


int main() {
    vector<bangBang> array = createMap("file");

    return 0;
}