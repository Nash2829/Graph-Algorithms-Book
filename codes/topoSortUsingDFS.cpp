// topoSortUsingDFS.cpp

#include "graph.hpp"

/**
 * @brief Helps topologicalSort by recursively applying DFS. Reversed topological ordering is stored in
 * order
 *
 * @param G The Graph Object.
 * @param u The vertex on which DFS is to be performed.
 * @param order The vector container in which reverse topological ordering is stored.
 * @param visited The vector boolean container to keep track of visited vertices.
 */
void 
topoSortUtil(const Graph &G, Vertex u, std::vector<Vertex> &order, std::vector<bool> &visited) {
    visited[u] = true;
    const std::vector<Vertex> & adj = G.getAdj(u);
    for (Vertex v : adj) {
        if (not visited[v]) 
            topoSortUtil(G, v, order, visited);
    }
    order.push_back(u);
}


/**
 * @brief Prints a topological ordering of the vertices if the Graph 
 * is an DAG. Prints an error message if the Graph is not an DAG.
 * 
 * @param G The Graph object
 * @param err Default = "IMPOSSIBLE". The error message to be prited
 * if the graph is not an DAG.
 */
void 
topologicalSort(const Graph &G, const std::string err = "IMPOSSIBLE") {
    int V = G.getV();
    int pos[V + 1]={};
    std::vector<Vertex> topologicalOrdering;
    topologicalOrdering.reserve(V);
    std::vector<bool> visited(V + 1);

    for (Vertex i = Vertex(1); i <= V; ++i) {
        if (not visited[i]) 
            topoSortUtil(G, i, topologicalOrdering, visited);
    }

    std::reverse(topologicalOrdering.begin(), topologicalOrdering.end());

    int p = 0;
    for (Vertex u : topologicalOrdering) {
        pos[u] = p; ++p;
    }

    for (Vertex i = Vertex(1); i <= V; ++i) {
        const std::vector<Vertex> &adj = G.getAdj(i);
        for (Vertex v : adj) {
            if (pos[v] < pos[i]) {
                std::cout << err << "\n";
                return; 
            }
        }
    }

    for (int u : topologicalOrdering) {
        std::cout << u << ' ';
    }
    std::cout << "\n";
}