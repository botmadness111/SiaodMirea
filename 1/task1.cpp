//
// Created by Andre on 24.09.2023.
//


#include <iostream>
#include <fstream>
#include <ostream>
#include <random>
#include <sstream>

using namespace std;

int getRegNum() {
    //srand(time(NULL));
    int min = 100000;
    int max = 999999;

    int num = min + rand() % (max - min + 1);
    return num;
}

string createFile() {
    string nameCompany = "OchenBezopasno";
    int regNum;
    string nameFile = "file";

    ofstream writeFile;
    writeFile.open(nameFile + ".txt", ios::trunc);
    writeFile.close();
    writeFile.open(nameFile + ".txt", ios::app);

    if (!writeFile) {
        cout << "No open file";
        return "";
    }

    for (int i = 0; i < 10; i++) {
        regNum = getRegNum();
        writeFile << nameCompany << " " << regNum << endl;
    }

    writeFile.close();
    return nameFile;
}

void updateToBinaryFile(string nameFile) {

    struct book {
        char nameCompany[20];
        int regNum;
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

    while (!readFile.eof()) {
        string line;
        getline(readFile, line);

        //---------------------------------------------------------
        string array[2];
        stringstream ss(line);
        string token;

        int index = 0;
        while (getline(ss, token, ' ')) {
            array[index] = token;
            index++;
        }
        //---------------------------------------------------------

        string nameCompany = array[0];

        char nameCompanyCharArray[20];
        copy(nameCompany.begin(), nameCompany.begin() + 20, nameCompanyCharArray);

        int regNum;
        if (!array[1].empty()) regNum = stoi(array[1]);
        else continue;

        book X;
        X.regNum = regNum;
        for (int i = 0; i < 20; i++) {
            X.nameCompany[i] = nameCompanyCharArray[i];
        }
        X.nameCompany[19] = ' ';

        writeFile.write((char *) &X, sizeof(book));
        writeFile << endl;

    }

    readFile.close();
    writeFile.close();
}

int main() {
    string nameFile = createFile();
    updateToBinaryFile(nameFile);


    return 0;
}


