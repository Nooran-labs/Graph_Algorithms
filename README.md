// noorangnaim@gmail.com
# Graph Algorithms Project in C++

## Overview

This project is a C++ implementation of classic **graph algorithms** using a custom `Graph` class without relying on STL containers like `vector` or `stack`. The project supports basic graph operations and several algorithms including:

- **Breadth-First Search (BFS)**
- **Depth-First Search (DFS)**
- **Dijkstra's Shortest Path**
- **Prim's Minimum Spanning Tree**
- **Kruskal's Minimum Spanning Tree**

All algorithms are tested and memory-safe, with unit tests written using the `doctest` framework.

---

## File Structure

```plaintext
.
├── Graph.h                    # Graph class definition
├── graphs.cpp                 # Graph class implementation
├── Algorithms.h               # Algorithms class definition
├── Algorithms.cpp             # Algorithms implementation
├── main.cpp                   # Demonstration main function
├── test_graph_algorithms.cpp  # Unit tests using doctest
├── doctest.h                  # Single-header unit testing framework
├── Makefile                   # Automates building, testing, and cleanup
```

---

## Graph Class

The `Graph` class is implemented using a **2D array (adjacency matrix)**. It represents an **undirected weighted graph**.

### Key Functions

- `addEdge(source, dest, weight)` — Adds a bi-directional edge.
- `removeEdge(source, dest)` — Removes an edge if it exists.
- `getEdgeWeight(u, v)` — Returns the weight of the edge, or -1 if none.
- `getAllEdges(count)` — Returns an array of all `Edge {src, dest, weight}`.
- `sumOfEdges()` — Returns the total weight of all edges.
- `print_graph()` — Displays the graph structure.
- `getNumVertices()` — Returns the number of vertices.

---

## Algorithms Class

The `Algorithms` class contains only **static methods**, which work on a `Graph` object.

### Pathfinding Algorithms

- `bfs(Graph&, int source)` — Returns a BFS tree rooted at the source.
- `dfs(Graph&, int source)` — Returns a DFS tree/forest.
- `dijkstra(Graph&, int source)` — Returns a shortest path tree using Dijkstra’s algorithm.

### Minimum Spanning Tree (MST)

- `prim(Graph&)` — Returns the MST using Prim's algorithm.
- `kruskal(Graph&)` — Returns the MST using Kruskal’s algorithm.

### Utility Methods

- `findPath(Graph&, int src, int dst, int& length)` — Finds a path using DFS (not necessarily the shortest).
- `getPathWeight(Graph&, int* path, int length)` — Sums weights of a path.

---

## Makefile Commands

The project includes a `Makefile` with the following useful commands:

- `make main` – Compiles and runs the demonstration file (`main.cpp`).
- `make test` – Compiles and runs the unit tests using `doctest`.
- `make valgrind` – Checks for memory leaks using Valgrind on the test suite.
- `make clean` – Deletes all compiled binaries and temporary files.

---

## Authors & Purpose

This project is structured to teach graph fundamentals and algorithm implementation **without STL**, giving more insight into lower-level programming and manual memory management.

---

## Dependencies

- [doctest.h](https://github.com/doctest/doctest): Lightweight single-header testing framework (included).

---

## Final Thoughts

This project is a clean, well-documented base for learning and experimenting with graph algorithms in C++. Easily extendable with more algorithms like Floyd-Warshall, Bellman-Ford, etc.
