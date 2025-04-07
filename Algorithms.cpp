// noorangnaim@gmail.com
#include "Algorithms.h"
#include <iostream>
#include <climits>
using namespace std;

Graph Algorithms::bfs(Graph& original, int source) {
    int n = original.getNumVertices();
    Graph bfsTree(n);
    cout << "\n--- BFS Tree from Vertex " << source << " ---\n";

    bool visited[100] = {false};
    int queue[100];
    int front = 0, rear = 0;

    visited[source] = true;
    queue[rear++] = source;

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < n; ++i) {
            int weight = original.getEdgeWeight(current, i);
            if (weight != -1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
                bfsTree.addEdge(current, i, weight);
            }
        }
    }

    return bfsTree;
}

Graph Algorithms::dfs(Graph& original, int source) {
    int n = original.getNumVertices();
    Graph dfsTree(n);
    cout << "\n--- DFS Tree from Vertex " << source << " ---\n";
    bool visited[100] = {false};
    dfsUtil(original, dfsTree, source, visited);
    return dfsTree;
}

void Algorithms::dfsUtil(Graph& original, Graph& dfsTree, int current, bool visited[]) {
    visited[current] = true;
    for (int i = 0; i < original.getNumVertices(); ++i) {
        int weight = original.getEdgeWeight(current, i);
        if (weight != -1 && !visited[i]) {
            dfsTree.addEdge(current, i, weight);
            dfsUtil(original, dfsTree, i, visited);
        }
    }
}

Graph Algorithms::dijkstra(Graph& original, int source) {
    int n = original.getNumVertices();
    Graph shortestTree(n);
    cout << "\n--- Dijkstra Shortest Path Tree from Vertex " << source << " ---\n";
    int dist[100], parent[100];
    bool visited[100] = {false};

    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[source] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = minDistance(dist, visited, n);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            int weight = original.getEdgeWeight(u, v);
            if (weight != -1 && !visited[v] && dist[u] != INT_MAX &&
                dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
            shortestTree.addEdge(parent[i], i, original.getEdgeWeight(parent[i], i));
        }
    }

    cout << "\nShortest paths from vertex " << source << ":" << endl;
    for (int v = 0; v < n; ++v) {
        if (v == source) continue;
        if (dist[v] == INT_MAX) {
            cout << "Vertex " << source << " -> " << v << " : No path." << endl;
        } else {
            cout << "Vertex " << source << " -> " << v << " : ";
            printPath(parent, v);
            cout << "\nSum of weights : " << dist[v] << "\n";
        }
    }

    return shortestTree;
}

int Algorithms::minDistance(int dist[], bool visited[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

int Algorithms::minKey(int key[], bool inMST[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < n; ++i) {
        if (!inMST[i] && key[i] < min) {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

void Algorithms::printPath(int parent[], int v) {
    if (parent[v] == -1) {
        cout << v;
        return;
    }
    printPath(parent, parent[v]);
    cout << " -> " << v;
}

Graph Algorithms::prim(Graph& original) {
    int n = original.getNumVertices();
    Graph mst(n);
    cout << "\n--- Prim's Minimum Spanning Tree ---\n";

    int key[100], parent[100];
    bool inMST[100] = {false};

    for (int i = 0; i < n; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = minKey(key, inMST, n);
        if (u == -1) break;
        inMST[u] = true;

        for (int v = 0; v < n; ++v) {
            int weight = original.getEdgeWeight(u, v);
            if (weight != -1 && !inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    int totalWeight = 0;
    for (int i = 1; i < n; ++i) {
        if (parent[i] != -1) {
            mst.addEdge(i, parent[i], original.getEdgeWeight(i, parent[i]));
            cout << "(" << i << " , " << parent[i] << ") , ";
            totalWeight += original.getEdgeWeight(i, parent[i]);
        }
    }
    cout << "\nSum of weights : " << totalWeight << endl;
    return mst;
}



Graph Algorithms::kruskal(Graph& original) {
    int n = original.getNumVertices();
    Graph mst(n);
    cout << "\n--- Kruskal's Minimum Spanning Tree ---\n";

    Edge edgeList[1000];
    int edgeCount = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (original.getEdgeWeight(i, j) != -1)
                edgeList[edgeCount++] = {i, j, original.getEdgeWeight(i, j)};

    // Selection sort
    for (int i = 0; i < edgeCount - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < edgeCount; ++j)
            if (edgeList[j].weight < edgeList[minIdx].weight)
                minIdx = j;
        if (minIdx != i) {
            Edge temp = edgeList[i];
            edgeList[i] = edgeList[minIdx];
            edgeList[minIdx] = temp;
        }
    }

    int parent[100];
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    auto find = [&](int v) {
        while (v != parent[v])
            v = parent[v];
        return v;
    };

    auto unionSets = [&](int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            parent[rootB] = rootA;
            return true;
        }
        return false;
    };

    int totalWeight = 0;
    for (int i = 0; i < edgeCount; ++i) {
        int u = edgeList[i].src;
        int v = edgeList[i].dest;
        int w = edgeList[i].weight;
        if (unionSets(u, v)) {
            mst.addEdge(u, v, w);
            cout << "(" << u << " , " << v << ") , ";
            totalWeight += w;
        }
    }
    cout << "\nSum of weights : " << totalWeight << endl;
    return mst;
}

// This function will help us navigate throw the algorithms
// Resulted trees and check for there correctness
int* Algorithms::findPath(Graph& graph, int src, int dst, int& pathLength) {
    int n = graph.getNumVertices();
    int edgeCount;
    Edge* edges = graph.getAllEdges(edgeCount);

    // Create adjacency list
    int adj[100][100];  // max 100 neighbors per vertex
    int adjSize[100] = {0};

    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;  // undirected
    }

    bool visited[100] = {false};
    int stack[100], top = 0;
    int parent[100];
    for (int i = 0; i < n; ++i) parent[i] = -1;

    stack[top++] = src;
    visited[src] = true;

    while (top > 0) {
        int u = stack[--top];
        if (u == dst) break;

        for (int i = 0; i < adjSize[u]; ++i) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                stack[top++] = v;
            }
        }
    }

    // Reconstruct path
    int path[100], len = 0;
    int current = dst;
    while (current != -1) {
        path[len++] = current;
        current = parent[current];
    }

    if (path[len - 1] != src) {
        // No path found
        pathLength = 0;
        delete[] edges;
        return nullptr;
    }

    // Reverse path
    int* result = new int[len];
    for (int i = 0; i < len; ++i)
        result[i] = path[len - 1 - i];

    pathLength = len;
    delete[] edges;
    return result;
}

// Helper function to find out the wieght of a given path in the graph
int Algorithms::getPathWeight(Graph& graph, int* path, int pathLength) {
    int total = 0;

    for (int i = 0; i < pathLength - 1; ++i) {
        int u = path[i];
        int v = path[i + 1];
        int weight = graph.getEdgeWeight(u, v);

        if (weight == -1) {
            return -1; // invalid path, edge missing
        }

        total += weight;
    }

    return total;
}


