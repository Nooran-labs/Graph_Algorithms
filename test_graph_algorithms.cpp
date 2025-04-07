// noorangnaim@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.h"
#include "Algorithms.h"

TEST_CASE("Graph basic operations") {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);

    CHECK(g.getEdgeWeight(0, 1) == 5);
    CHECK(g.getEdgeWeight(1, 0) == 5);
    CHECK(g.getEdgeWeight(0, 3) == -1);
    CHECK(g.sumOfEdges() == 11);
    
    int pathLength;
    int* path = Algorithms::findPath(g, 1, 3, pathLength);
    CHECK(path != nullptr);
    CHECK(pathLength == 2);
    int weight = Algorithms::getPathWeight(g, path, pathLength);
    CHECK(weight == 2);
    delete[] path;
    

    g.removeEdge(1, 2);
    CHECK(g.getEdgeWeight(1, 2) == -1);

    CHECK_THROWS(g.removeEdge(1, 2)); // Should throw since edge was removed
}

TEST_CASE("BFS Tree correctness") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 1);

    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK(bfsTree.getEdgeWeight(0, 1) == 1);
    CHECK(bfsTree.getEdgeWeight(0, 2) == 1);
}

TEST_CASE("DFS Tree correctness") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    
    int pathLength;
    int pathExp[] = {0, 1, 3};
    int* pathRes = Algorithms::findPath(g, 0, 3, pathLength);
    CHECK(pathRes != nullptr);
    CHECK(pathLength == 3);
    CHECK(pathExp[0] == pathRes[0]);
    CHECK(pathExp[1] == pathRes[1]);
    CHECK(pathExp[2] == pathRes[2]);
    delete[] pathRes;

    Graph dfsTree = Algorithms::dfs(g, 0);
    
    CHECK(dfsTree.getEdgeWeight(0, 1) != -1);
    CHECK(dfsTree.getEdgeWeight(1, 3) != -1);
}

TEST_CASE("Dijkstra: findPath + getPathWeight") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 3);

    int pathLength;
    Graph result = Algorithms::dijkstra(g, 0);
    int* path = Algorithms::findPath(result, 0, 4, pathLength);
    CHECK(path != nullptr);

    int weight = Algorithms::getPathWeight(result, path, pathLength);
    CHECK(weight == 8); // 0 -> 1 -> 2 -> 3 -> 4 (2+2+1+3)

    delete[] path;
}

TEST_CASE("Prim and Kruskal MST total weight matches") {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);

    Graph primMST = Algorithms::prim(g);
    Graph kruskalMST = Algorithms::kruskal(g);

    int primWeight = primMST.sumOfEdges();
    int kruskalWeight = kruskalMST.sumOfEdges();

    CHECK(primWeight == kruskalWeight);
    CHECK(primWeight == 14); // expected MST weight: 3+1+2+2+6
}
