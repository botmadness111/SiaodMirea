//
// Created by Andre on 08.10.2023.
//

#include <fstream>
#include "iostream"

using namespace std;

class HashTableBin {

    struct book {
        char eng[15];
        char rus[15];
    };

    int size;
    int *hashTable; //offsets
    string *hashTableKeys;

    int cnt;

public:

    HashTableBin() {
        this->size = 5;
        this->hashTable = new int[size];
        this->hashTableKeys = new string[size];

        for (int i = 0; i < size; i++) {
            hashTable[i] = -1;
            hashTableKeys[i] = "";
        }

        this->cnt = 0;

    }

    void put(string &key, int &val) {

        if (get(key) != -1) return;

        int hashCode = getHashCode(key);

        int isInclude = hashTable[hashCode]; //check empty or not place
        if (isInclude == -1 || isInclude == -2) {
            this->hashTable[hashCode] = val;
            this->hashTableKeys[hashCode] = key;
            this->cnt++;
            //cout << key << ": " << hashCode << endl;
        } else {
            int start = hashCode;
            hashCode = (hashCode + 1) % this->size;
            while (hashCode != start) { //find first empty place
                isInclude = this->hashTable[hashCode];
                if (isInclude == -1 || isInclude == -2) {
                    this->hashTable[hashCode] = val;
                    this->hashTableKeys[hashCode] = key;
                    //cout << key << ": " << hashCode << endl;
                    this->cnt++;
                    break;
                }
                hashCode = (hashCode + 1) % this->size;
            }
        }

        if (double(this->cnt) / double(this->size) >= 0.75) { //rehash
            rehesh();
        }
    }

    int get(string &key) {
        int hashCode = getHashCode(key);
        if (this->hashTableKeys[hashCode] == key) return this->hashTable[hashCode]; // if find

        int start = hashCode;

        hashCode = (hashCode + 1) % this->size;
        while (start != hashCode) { //bypass all map
            if (this->hashTableKeys[hashCode].empty()) return -1; //если пустой, значит правее уже ничего не будет
            if (this->hashTableKeys[hashCode] == key) return this->hashTable[hashCode]; // if finded

            hashCode = (hashCode + 1) % this->size;
        }

        return -1;

    }

    string getByBin(string &key) {
        int offset = get(key);
        if (offset == -1) return "Error";

        string result = "";

        book X;

        string nameFile = "base3";
        ifstream readFile(nameFile + ".bin", ios::binary);
        readFile.seekg(offset);
        readFile.read((char *) &X, sizeof(book));

        for (auto chr: X.rus) {
            result += chr;
        }
        readFile.close();
        return result;
    }

    void remove(string &key) {
        int hashCode = getHashCode(key);
        if (this->hashTableKeys[hashCode] == key) { // if find

            int offset = hashTable[hashCode];


            this->hashTable[hashCode] = -2;
            this->hashTableKeys[hashCode] = "";
            this->cnt--;

            rewriteBin(offset);

            return;
        }

        int start = hashCode;

        hashCode = (hashCode + 1) % this->size;
        while (start != hashCode) { //обходим всю мапу
            if (this->hashTableKeys[hashCode].empty()) return; //если пустой, значит правее уже ничего не будет
            if (this->hashTableKeys[hashCode] == key) {

                int offset = hashTable[hashCode];

                this->hashTable[hashCode] = -2; // если нашли
                this->hashTableKeys[hashCode] = "";
                this->cnt--;

                rewriteBin(offset);
                return;
            }

            hashCode = (hashCode + 1) % this->size;
        }
    }

    void rewriteBin(int offset) {
        string nameFile = "base3";
        string nameFileNew = "tmp";

        ifstream readFile(nameFile + ".bin", ios::binary);

        ofstream writeFile1(nameFileNew + ".bin", ios::trunc);
        writeFile1.close();

        ofstream writeFile(nameFileNew + ".bin", ios::in | ios::binary | ios::app);

        book X;
        int k = 0;
        while (!readFile.eof()) {
            readFile.read((char *) &X, sizeof(book));
            char *eng = X.eng;
            char *rus = X.rus;
            string rusStr = rus;
            string engStr = eng;

            if (rusStr.empty()) continue;

            char rusCharArray[15];
            copy(rusStr.begin(), rusStr.begin() + 15, rusCharArray);

            if (engStr.empty()) continue;

            char engCharArray[15];
            copy(engStr.begin(), engStr.begin() + 15, engCharArray);

            for (int i = 0; i < 15; i++) {
                X.rus[i] = rusCharArray[i];
            }
            for (int i = 0; i < 15; i++) {
                X.eng[i] = engCharArray[i];
            }

            int offsetTmp = k * sizeof(book);
            if (offsetTmp == offset) continue;

            if (offsetTmp != offset) {
                writeFile.write((char *) &X, sizeof(book));
            }

            k++;

        }
        readFile.close();
        writeFile.close();

        string readFilee = "tmp";
        string writeFilee = "base3";

        ifstream readFile2(readFilee + ".bin", ios::binary);

        ofstream writeFile3(writeFilee + ".bin", ios::trunc);
        writeFile1.close();

        ofstream writeFile2(writeFilee + ".bin", ios::in | ios::binary | ios::app);

        while (!readFile2.eof()) {
            readFile2.read((char *) &X, sizeof(book));
            char *eng = X.eng;
            char *rus = X.rus;
            string rusStr = rus;
            string engStr = eng;

            if (rusStr.empty()) continue;

            char rusCharArray[15];
            copy(rusStr.begin(), rusStr.begin() + 15, rusCharArray);

            if (engStr.empty()) continue;

            char engCharArray[15];
            copy(engStr.begin(), engStr.begin() + 15, engCharArray);

            for (int i = 0; i < 15; i++) {
                X.rus[i] = rusCharArray[i];
            }
            for (int i = 0; i < 15; i++) {
                X.eng[i] = engCharArray[i];
            }


            writeFile2.write((char *) &X, sizeof(book));

        }
        readFile2.close();
        writeFile2.close();
    }

    void print() {
        for (int i = 0; i < size; i++) {
            string key = this->hashTableKeys[i];
            int val = this->hashTable[i];
            if (!key.empty()) cout << key << +": " << val << endl;
        }
    }


private:
    int getSum(string &key) {
        int sum = 0;
        for (auto symbol: key) {
            sum += abs((int) symbol);
        }
        return sum;
    }

    int getHashCode(string &key) {
        int sum = getSum(key);
        int hashCode = sum % this->size;

        return hashCode;
    }

    int getHashCode(string &key, int size) {
        int sum = getSum(key);
        int hashCode = sum % size;

        return hashCode;
    }

    int get(int *&hashTable, string *&hashTableKeys, string &key) {
        int hashCode = getHashCode(key, this->size / 2);
        if (hashTableKeys[hashCode] == key) return hashTable[hashCode]; // if find

        int start = hashCode;

        hashCode = (hashCode + 1) % (this->size / 2);
        while (start != hashCode) { //bypass all map
            if (hashTableKeys[hashCode].empty()) return -1; //если пустой, значит правее уже ничего не будет
            if (hashTableKeys[hashCode] == key) return hashTable[hashCode]; // if find

            hashCode = (hashCode + 1) % (this->size / 2);
        }

        return -1;

    }

    void rehesh() {

        this->size *= 2;
        int *hashTableTmp = hashTable;
        string *hashTableKeysTmp = hashTableKeys;

        this->hashTable = new int[size];
        this->hashTableKeys = new string[size];
        for (int i = 0; i < size; i++) {
            hashTable[i] = -1;
            hashTableKeys[i] = "";
        }
        this->cnt = 0;


        for (int i = 0; i < this->size / 2; i++) { //перезаписыаем старые ключи в новую мапу с новым размером
            string key = hashTableKeysTmp[i];
            int val = get(hashTableTmp, hashTableKeysTmp, key);
            put(key, val);
        }


    }
};