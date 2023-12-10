//
// Created by Andre on 12.11.2023.
//

#include <iostream>
#include <vector>
#include <queue>
#include "Node.cpp"
#include <cmath>
#include <fstream>

using namespace std;

class BinarySearchTree {
    int const STEP = 15;

public:
    struct book {
        char rus[15];
    };


private:
    int offset = 0;
    Node *head;

public:
    BinarySearchTree() {
        head = nullptr;
    };

    bool add(string name, string translate) {
        return addBinary(name, translate);
    }

    string get(string name) {
        return getBinary(name);
    }

    bool remove(string name) {
        return removeBinary(name);
    }

    void printTree() {
        printBinaryTree();
    }

private:
    string getTranslate(string nameFile, int offset) {
        string result = "";

        book X;
        ifstream readFile(nameFile + ".bin", ios::binary);
        readFile.seekg(offset);
        readFile.read((char *) &X, sizeof(book));
        for (auto chr: X.rus) {
            result += chr;
        }
        readFile.close();
        return result;
    }

    void writeToBinaryFile(string nameFile, string name) {

        ofstream writeFile(nameFile + ".bin", ios::in | ios::binary | ios::app);

        if (!writeFile) {
            cout << "No open file: " << nameFile << ".bin";
            return;
        }

        book X;
        for (int i = 0; i < 15; i++) {
            if (i >= name.length()){
                X.rus[i] = '_';
            }
            else{
                X.rus[i] = name[i];
            }

        }

        writeFile.write((char *) &X, sizeof(book));

        writeFile.close();
    }

    int getOffset() {
        offset += STEP;
        return offset - STEP;
    }

    bool addBinary(string &name, string &translate) {
        if (head == nullptr) {
            int offset2 = getOffset();
            head = new Node(name, offset2);
            writeToBinaryFile("fileTree", translate);
            return true;
        } else {
            Node *current = head;
            while (true) {
                if (name >= current->key) {
                    if (current->right != nullptr) current = current->right;
                    else {
                        int offset2 = getOffset();
                        current->right = new Node(name, offset2);
                        current->right->past = current;
                        writeToBinaryFile("fileTree", translate);
                        return true;
                    }
                } else {
                    if (current->left != nullptr) current = current->left;
                    else {
                        int offset2 = getOffset();
                        current->left = new Node(name, offset2);
                        current->left->past = current;
                        writeToBinaryFile("fileTree", translate);
                        return true;
                    }
                }
            }
            return false;

        }
    }

    string getBinary(string &name) {
        Node *current = head;
        while (current != nullptr) {
            if (name > current->key) {
                current = current->right;
            } else if (name < current->key) {
                current = current->left;
            } else {
                int offset2 = current->getOffset();
                return getTranslate("fileTree", offset2);
            }
        }
        return "Error";
    }

    bool removeBinary(string &name) {
        Node *current = head;
        while (current != nullptr) {
            if (name > current->key) {
                current = current->right;
            } else if (name < current->key) {
                current = current->left;
            } else {
                if (current == head) {
                    if (head->left != nullptr) {
                        Node *tmp = head->right;
                        head = head->left;
                        current = head;
                        while (current->right != nullptr) {
                            current = current->right;
                        }
                        current->right = tmp;
                    } else if (head->right != nullptr) {
                        Node *tmp = head->left;
                        head = head->right;
                        current = head;
                        while (current->left != nullptr) {
                            current = current->left;
                        }
                        current->left = tmp;
                    } else {
                        head = nullptr;
                    }
                    return true;
                }

                if (current == current->past->right) {
                    if (current->left == nullptr) {
                        current->past->right = current->right;
                        return true;
                    } else if (current->right == nullptr) {
                        current->past->right = current->left;
                        return true;
                    } else if (current->right != nullptr && current->left != nullptr) {
                        Node *tmp = current->left;

                        current->past->right = current->right;

                        Node *goLeft = current->right;
                        while (goLeft->left != nullptr) {
                            goLeft = goLeft->left;
                        }
                        goLeft->left = tmp;
                        return true;
                    } else {
                        current->past->right = nullptr;
                        return true;
                    }

                    return false;


                } else {
                    if (current->right == nullptr) {
                        current->past->left = current->left;
                        return true;
                    } else if (current->left == nullptr) {
                        current->past->left = current->right;
                        return true;
                    } else if (current->left != nullptr && current->right != nullptr) {
                        Node *tmp = current->right;

                        current->past->left = current->left;

                        Node *goRight = current->left;
                        while (goRight->right != nullptr) {
                            goRight = goRight->right;
                        }
                        goRight->right = tmp;
                        return true;

                    } else {
                        current->past->left = nullptr;
                        return true;
                    }

                    return false;
                }

                return false;

            }
        }
        return false;

    }

    vector<string> helper(queue<Node> queue) { //return all children
        vector<string> vector;
        while (!queue.empty()) {
            Node *node = &queue.front();
            queue.pop();

            if (node->left != nullptr) {
                vector.push_back(node->left->key);
            } else {
                vector.push_back("*");
            }
            if (node->right != nullptr) {
                vector.push_back(node->right->key);
            } else {
                vector.push_back("*");
            }

        }
        return vector;
    }

    void breadthFirstSearch(vector<vector<string>> &bfs) {
        queue<Node> queuee;
        queuee.push(*head);

        vector<string> children;
        children.push_back(head->key);
        bfs.push_back(children);
        bfs.push_back(helper(queuee));

        while (!queuee.empty()) {
            int k = 0;
            int kk = 0;
            queue<Node> queueTmp;
            while (!queuee.empty()) {
                Node *node = &queuee.front();
                queuee.pop();

                if (node->getOffset() == -1) k++;
                kk++;


                if (node->left != nullptr) queueTmp.push(*node->left);
                else queueTmp.push(*new Node("*", -1));

                if (node->right != nullptr) queueTmp.push(*node->right);
                else queueTmp.push(*new Node("*", -1));

            }
            if (k == kk) {
                return;
            }

            //rewrite from queueTmp to queue
            while (!queueTmp.empty()) {
                queuee.push(queueTmp.front());
                queueTmp.pop();
            }

            children = helper(queuee);
            bfs.push_back(children);
        }
    }

    void printBinaryTree() {
        vector<vector<string>> bfs;

        breadthFirstSearch(bfs);

        int deep = bfs.size() - 1;
        int max = pow(2, deep);

        int start = max / 3;
        int end = start * 2;
        int cnt = 1;

        for (auto items: bfs) {

            int step = (end - start) / cnt;
            for (auto item: items) {

                for (int j = 0; j < step; j++) {
                    cout << " ";
                }

                cout << item << " ";
                step += step / (cnt);

            }
            cout << endl;

            end += 1; // change!!!
            cnt *= 2;
        }
    }
};


