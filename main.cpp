// noorangnaim@gmail.com
#include "Graph.h"
#include "Algorithms.h"
#include <iostream>

int main() {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);

    std::cout << "Original Graph:\n";
    g.print_graph();

    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    dijkstraTree.print_graph();

    Graph primMST = Algorithms::prim(g);
    primMST.print_graph();

    Graph kruskalMST = Algorithms::kruskal(g);
    kruskalMST.print_graph();

    return 0;
}
