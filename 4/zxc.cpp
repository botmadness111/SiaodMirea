#include "iostream"
#include <stack>
#include <queue>

using namespace std;

int main() {
    queue<int> qu;
    qu.push(2);
    qu.push(1);
    qu.push(4);

    cout << qu.front() << endl;
    qu.pop();
    cout << qu.front() << endl;
}