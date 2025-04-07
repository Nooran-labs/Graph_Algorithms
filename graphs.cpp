// noorangnaim@gmail.com
#include "Graph.h"

Graph::Graph(int vertices) {
    if (vertices > MAX_VERTICES) throw invalid_argument("Too many vertices.");
    if (vertices == 0) throw invalid_argument("Can't make a grapgh with 0 vertices!");
    numVertices = vertices;
    for (int i = 0; i < numVertices; ++i)
        for (int j = 0; j < numVertices; ++j)
            adjMatrix[i][j] = -1;
}

// Don't forget to free memory when using it
Edge* Graph::getAllEdges(int& count) {
    count = 0;

    // Max possible edges = (n * (n-1)) / 2 for undirected graph
    Edge* edges = new Edge[numVertices * numVertices];

    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (adjMatrix[i][j] != -1) {
                edges[count++] = {i, j, adjMatrix[i][j]};
            }
        }
    }

    return edges;
}

void Graph::addEdge(int source, int dest, int weight) {
    if (!isValidVertex(source) || !isValidVertex(dest)) return;
    adjMatrix[source][dest] = weight;
    adjMatrix[dest][source] = weight;
}

void Graph::removeEdge(int source, int dest) {
    if (!isValidVertex(source) || !isValidVertex(dest)) return;
    if (adjMatrix[source][dest] == -1)
        throw runtime_error("No edge exists.");
    adjMatrix[source][dest] = -1;
    adjMatrix[dest][source] = -1;
}

void Graph::print_graph() {
    cout << "Graph adjacency matrix:\n";
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": ";
        for (int j = 0; j < numVertices; ++j)
            if (adjMatrix[i][j] != -1)
                cout << "(" << j << ", weight: " << adjMatrix[i][j] << ") ";
        cout << endl;
    }
}

bool Graph::isValidVertex(int v) {
    return (v >= 0 && v < numVertices);
}

int Graph::sumOfEdges() {
    int total = 0;

    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) { // avoid double-counting
            if (adjMatrix[i][j] != -1) {
                total += adjMatrix[i][j];
            }
        }
    }

    return total;
}
