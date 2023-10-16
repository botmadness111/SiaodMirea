//
// Created by Andre on 08.10.2023.
//

#include "Hash.h"
#include "iostream"

using namespace std;

class HashTable {

    int size;
    string *hashTable;
    string *hashTableKeys;

    int cnt;

public:

    HashTable() {
        this->size = 5;
        this->hashTable = new string[size];
        this->hashTableKeys = new string[size];

        for (int i = 0; i < size; i++) {
            hashTable[i] = "";
            hashTableKeys[i] = "";
        }

        this->cnt = 0;

    }

    void put(string &key, string &val) {

        int hashCode = getHashCode(key);

        string isInclude = hashTable[hashCode]; //???????? ???????? ?? ??????
        if (isInclude.empty() || isInclude == "*") {
            this->hashTable[hashCode] = val;
            this->hashTableKeys[hashCode] = key;
            this->cnt++;
            //cout << key << ": " << hashCode << endl;
        } else {
            int start = hashCode;
            hashCode = (hashCode + 1) % this->size;
            while (hashCode != start) { //???? ?????? ??????????-????????? ??????
                isInclude = this->hashTable[hashCode];
                if (isInclude.empty() || isInclude == "*") {
                    this->hashTable[hashCode] = val;
                    this->hashTableKeys[hashCode] = key;
                    //cout << key << ": " << hashCode << endl;
                    this->cnt++;
                    break;
                }
                hashCode = (hashCode + 1) % this->size;
            }
        }
        if (double(this->cnt) / double(this->size) >= 0.75) { //?????????????
            rehesh();
        }
    }

    string get(string &key) {
        int hashCode = getHashCode(key);
        if (this->hashTableKeys[hashCode] == key) return this->hashTable[hashCode]; // ???? ?????

        int start = hashCode;

        hashCode = (hashCode + 1) % this->size;
        while (start != hashCode) { //??????? ??? ????
            if (this->hashTableKeys[hashCode].empty()) return ""; //???? ??????, ?????? ?????? ??? ?????? ?? ?????
            if (this->hashTableKeys[hashCode] == key) return this->hashTable[hashCode]; // ???? ?????

            hashCode = (hashCode + 1) % this->size;
        }

        return "";

    }

    void remove(string &key) {
        int hashCode = getHashCode(key);
        if (this->hashTableKeys[hashCode] == key) { // ???? ?????
            this->hashTable[hashCode] = "*";
            this->hashTableKeys[hashCode] = "";
            this->cnt--;
            return;
        }

        int start = hashCode;

        hashCode = (hashCode + 1) % this->size;
        while (start != hashCode) { //??????? ??? ????
            if (this->hashTableKeys[hashCode].empty()) return; //???? ??????, ?????? ?????? ??? ?????? ?? ?????
            if (this->hashTableKeys[hashCode] == key) {
                this->hashTable[hashCode] = "*"; // ???? ?????
                this->hashTableKeys[hashCode] = "";
                this->cnt--;
                return;
            }

            hashCode = (hashCode + 1) % this->size;
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            string key = this->hashTableKeys[i];
            string val = this->hashTable[i];
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

    string get(string *&hashTable, string *&hashTableKeys, string &key) {
        int hashCode = getHashCode(key, this->size / 2);
        if (hashTableKeys[hashCode] == key) return hashTable[hashCode]; // ???? ?????

        int start = hashCode;

        hashCode = (hashCode + 1) % (this->size / 2);
        while (start != hashCode) { //??????? ??? ????
            if (hashTableKeys[hashCode].empty()) return ""; //???? ??????, ?????? ?????? ??? ?????? ?? ?????
            if (hashTableKeys[hashCode] == key) return hashTable[hashCode]; // ???? ?????

            hashCode = (hashCode + 1) % (this->size / 2);
        }

        return "";

    }

    void rehesh() {

        this->size *= 2;
        string *hashTableTmp = hashTable;
        string *hashTableKeysTmp = hashTableKeys;

        this->hashTable = new string[size];
        this->hashTableKeys = new string[size];
        this->cnt = 0;


        for (int i = 0; i < this->size / 2; i++) { //????????????? ?????? ????? ? ????? ???? ? ????? ????????
            string key = hashTableKeysTmp[i];
            string val = get(hashTableTmp, hashTableKeysTmp, key);
            put(key, val);
        }


    }
};