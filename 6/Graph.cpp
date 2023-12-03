#include <iostream>
#include <utility>
#include "MyNode.cpp"


using namespace std;

class Graph {
private:
    const int INF = 99999999;
    int cnt = 0;
    vector<string> keys;

    unordered_map<string, vector<string>> *bdPath = nullptr;
    unordered_map<string, int> *bdCost = nullptr;

public:
    Graph() {
        bdPath = new unordered_map<string, vector<string>>;
        bdCost = new unordered_map<string, int>;

    }

    void print() {
        cout << "   ";
        for (const auto &key: keys) {
            cout << key + "  ";
        }
        cout << endl;

        for (const auto &key: keys) {
            cout << key << "  ";

            for (const auto &val: keys) {
                bool flag = true;
                for (auto item: (*bdPath)[key]) {
                    if (val == item) {
                        cout << (*bdCost)[key + val] << "  ";
                        flag = false;
                        break;
                    }
                }
                if (flag) cout << 0 << "  ";
            }
            cout << endl;
        }
    }

    void add(const string &x, const string &y, int cost) {

        bool flag1 = true, flag2 = true;
        for (auto key: keys) {
            if (key == x) flag1 = false;
            if (key == y) flag2 = false;
        }

        if (flag1) {
            keys.push_back(x);
            cnt++;
        }
        if (flag2) {
            keys.push_back(y);
            cnt++;
        }


        if ((*bdPath)[x].empty()) { //not addition
            (*bdPath)[x] = {y};
            (*bdCost)[x + y] = cost;

        } else {
            (*bdPath)[x].push_back(y);
            (*bdCost)[x + y] = cost;
        }

    }

    void printMinPath(const string &X, const string &Y) {
        vector<MyNode> costs;

        for (int k = 0; k < cnt; k++) {
            if (keys[k] != X) {
                MyNode *node = new MyNode(nullptr, keys[k], INF);
                costs.push_back(*node);
            } else {
                MyNode *node = new MyNode(nullptr, keys[k], 0);
                costs.push_back(*node);
            }

        }

        vector<MyNode> costsTmp;
        for (int i = 0; i < cnt; i++) {

            costsTmp.clear();
            for (auto node: costs) {
                costsTmp.push_back(node);
            }

            for (int index = 0; index < cnt; index++) {

                int cost = costs[index].value;

                if (cost != INF) {
                    string x = keys[index];

                    vector<string> nexts = (*bdPath)[x];
                    for (const auto &y: nexts) {
                        int nextCost = (*bdCost)[x + y];

                        int indexIntoCosts = getIndexIntoCosts(y);
                        if (cost + nextCost < costsTmp[indexIntoCosts].value) { //new or current
                            MyNode *newNode = new MyNode(&costs[index], costsTmp[indexIntoCosts].key, cost + nextCost);
                            costsTmp[indexIntoCosts] = *newNode;
                        }

                    }
                }
            }

            for (int j = 0; j < costsTmp.size(); j++) {
                costs[j] = costsTmp[j];
            }
        }

        vector<string> array;
        for (auto node: costs) {
            if (node.key == Y) {
                while (node.past != nullptr) {
                    array.push_back(node.key);
                    node = *node.past;
                }
                break;
            }
        }
        array.push_back(X);
        std::reverse(array.begin(), array.end());
        cout << "Path is: ";
        for (const auto& key: array){
            cout << key << " ";
        }

    };

    int getMinPathCost(const string &X, const string &Y) {
        vector<int> costs;

        for (int k = 0; k < cnt; k++) {
            if (keys[k] != X) costs.push_back(INF);
            else costs.push_back(0);

        }

        vector<int> costsTmp;
        for (int i = 0; i < cnt; i++) {

            costsTmp.clear();
            for (auto val: costs) {
                costsTmp.push_back(val);
            }

            for (int index = 0; index < cnt; index++) {

                int cost = costs[index];

                if (cost != INF) {
                    string x = keys[index];

                    vector<string> nexts = (*bdPath)[x];
                    for (const auto &y: nexts) {
                        int nextCost = (*bdCost)[x + y];

                        int indexIntoCosts = getIndexIntoCosts(y);
                        costsTmp[indexIntoCosts] = min(cost + nextCost, costsTmp[indexIntoCosts]); //new or current
                    }
                }
            }

            for (int j = 0; j < costsTmp.size(); j++) {
                costs[j] = costsTmp[j];
            }
        }


        int indexIntoCosts = getIndexIntoCosts(Y);
        return costs[indexIntoCosts];
    }

    int getIndexIntoCosts(const string &y) {
        for (int index = 0; index < keys.size(); index++) {
            if (y == keys[index]) return index;
        }
        return -1;
    };

    int getEccentricity(const string &x) {
        int maxx = -999999999;
        for (const auto &y: keys) {
            if (x != y) {
                int cost = max(getMinPathCost(x, y), maxx);
                if (cost != INF) maxx = max(cost, maxx);
            }
        }
        return maxx;
    }
};