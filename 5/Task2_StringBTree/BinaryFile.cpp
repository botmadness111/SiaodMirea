//
// Created by Andre on 13.11.2023.
//
#include "iostream"
#include <fstream>
#include <ostream>

using namespace std;

class BinaryFile {
public:
    void updateToBinaryFile(string nameFile) {

        struct book {
            char rus[15];
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

//        int k = 0;
//        while (!readFile.eof()) {
//            string eng;
//            getline(readFile, eng);
//
//            //---------------------------------------------------------
//
//
//
//            if (eng.empty()) continue;
//
//            char engCharArray[15];
//            copy(eng.begin(), eng.begin() + 15, engCharArray);
//
//            book X;
//            for (int i = 0; i < 15; i++) {
//                X.rus[i] = engCharArray[i];
//            }
//
//            writeFile.write((char *) &X, sizeof(book));
//
//            k++;
//        }

        readFile.close();
        writeFile.close();

    }

    void makeSelect(string nameFile, BTree &tree){

        ifstream readFile(nameFile + ".txt", ios::in);

        if (!readFile.is_open()) {
            cout << "No open file: " << nameFile << ".txt";
            return;
        }

        while (!readFile.eof()) {
            string eng;
            string rus;
            getline(readFile, eng);
            getline(readFile, rus);

            if (eng.empty() || rus.empty()) continue;

            tree.add(eng, rus);

        }
        readFile.close();

    }
};


