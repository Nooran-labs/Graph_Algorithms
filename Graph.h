// noorangnaim@gmail.com
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX_VERTICES = 100;
struct Edge {
    int src;
    int dest;
    int weight;
};

class Graph {
private:
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;

public:
    Graph(int vertices);
    void addEdge(int source, int dest, int weight);
    void removeEdge(int source, int dest);
    void print_graph();
    Edge* getAllEdges(int& count);
    int getEdgeWeight(int u, int v) const { return adjMatrix[u][v]; }
    int getNumVertices() const { return numVertices; }
    int sumOfEdges();

private:
    bool isValidVertex(int v);
};

#endif
