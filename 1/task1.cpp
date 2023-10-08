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

    for (int i = 1000000; i < 1000999; i++) {
        regNum = getRegNum();
        writeFile << nameCompany << endl << i << endl;
    }

    writeFile.close();
    return nameFile;
}

void updateToBinaryFile(string nameFile) {

    struct book {
        char nameCompany[14];
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
        string nameCompany;
        string regNumStr;
        getline(readFile, nameCompany);
        getline(readFile, regNumStr);

        //---------------------------------------------------------

        //string nameCompany = array[0];
        if (nameCompany.empty()) continue;

        char nameCompanyCharArray[14];
        copy(nameCompany.begin(), nameCompany.begin() + 14, nameCompanyCharArray);

        int regNum;
        if (!regNumStr.empty()) regNum = stoi(regNumStr);
        else continue;

        book X;
        X.regNum = regNum;
        for (int i = 0; i < 14; i++) {
            X.nameCompany[i] = nameCompanyCharArray[i];
        }

        writeFile.write((char *) &X, sizeof(book));


    }

    readFile.close();
    writeFile.close();
}

int main() {
    string nameFile = createFile();
    updateToBinaryFile(nameFile);


    return 0;
}


