#include "iostream"
#include "HashTable.cpp"
#include <fstream>
#include <ostream>

using namespace std;

void updateToBinaryFile(string nameFile) {

    struct book {
        char rus[15];
        char eng[15];
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
        string rus;
        string eng;
        getline(readFile, rus);
        getline(readFile, eng);

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

        writeFile.write((char *) &X, sizeof(book));


    }

    readFile.close();
    writeFile.close();


}

void updateToHashTable(string nameFile, HashTable& map) {

    struct book {
        char rus[15];
        char eng[15];
    };

    // считывание с файла
    ifstream readFile(nameFile + ".bin", ios::binary);
    book X;

    while (!readFile.eof()) {
        readFile.read((char *) &X, sizeof(book));
        char *rus = X.rus;
        char *eng = X.eng;
        string rusStr = rus;
        string engStr = eng;
        map.put(rusStr, engStr);
        //cout << rus << " " << eng << endl;

    }
    readFile.close();
}


int main() {
    setlocale(LC_ALL, "Russian");
    updateToBinaryFile("base");
    HashTable map = *new HashTable();

    //fill map
    cout << "--------------------" << endl;
    updateToHashTable("base", map);
    map.print();

    //delete element of map
    cout << "--------------------" << endl;
    string key = "Strong";
    map.remove(key);

    key = "New";
    map.remove(key);

    key = "Hot";
    map.remove(key);

    map.print();

    //get element of map
    cout << "--------------------" << endl;

    key = "Hot";
    cout << map.get(key) << endl;

    key = "School";
    cout << map.get(key) << endl;

    key = "Doctor";
    cout << map.get(key) << endl;

    key = "Sad";
    cout << map.get(key) << endl;


    return 0;
}
