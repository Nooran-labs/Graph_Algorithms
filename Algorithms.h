// noorangnaim@gmail.com
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"


class Algorithms {
public:
    static Graph bfs(Graph& original, int source);
    static Graph dfs(Graph& original, int source);
    static Graph dijkstra(Graph& original, int source);
    static Graph prim(Graph& original);
    static Graph kruskal(Graph& original);
    static int* findPath(Graph& graph, int src, int dst, int& pathLength);
    static int getPathWeight(Graph& graph, int* path, int pathLength);

private:
    static void dfsUtil(Graph& original, Graph& dfsTree, int current, bool visited[]);
    static int minDistance(int dist[], bool visited[], int n);
    static int minKey(int key[], bool inMST[], int n);
    static void printPath(int parent[], int v);
};

#endif
