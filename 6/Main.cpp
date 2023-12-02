#include <iostream>

#include "string"
#include "unordered_map"
#include "vector"
#include <algorithm>

#include "Graph.cpp"

using namespace std;

int main() {

    Graph graph = *new Graph();
    graph.add("1", "2", 2);
    graph.add("2", "5", 10);
    graph.add("5", "6", 3);
    graph.add("1", "3", 5);
    graph.add("3", "4", 9);
    graph.add("4", "6", 4);
    graph.add("2", "4", 6);
    graph.add("3", "5", 8);

    cout << graph.getMinPathCost("3", "6") << endl;
    //graph.printMinPath("3", "6");

    //graph.print();

    //cout << graph.getEccentricity("1") << endl;


    return 0;
}