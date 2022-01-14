// topoSortUsingKahn.cpp

#include "graph.hpp" 

/**
 * @brief Prints a topological ordering of the vertices if the Graph 
 * is an DAG. Prints an error message if the Graph is not an DAG.
 * 
 * @param G The Graph object
 * @param err Default = "IMPOSSIBLE". The error message to be prited
 * if the graph is not an DAG.
 */
void
topologicalSort(const Graph &G, const std::string& err = "IMPOSSIBLE") {
    int V = G.getV();
    Vertex inDegree[V + 1]={};
    std::queue<Vertex> Q;
    std::vector<Vertex> topologicalOrdering;
    topologicalOrdering.reserve(V);

    // Count incoming edges for all vertices
    for (Vertex u = Vertex(1); u <= V; ++u) {
        const std::vector<Vertex> & adj = G.getAdj(u);
        for (Vertex v : adj) {
            inDegree[v]++;
        }
    }

    for (Vertex u = Vertex(1); u <= V; ++u) {
        // Enqueue the vertex with 0 in-degree
        if (inDegree[u] == 0) 
            Q.push(u);          
    }

    while (not Q.empty()) {
        Vertex u = Q.front();
        Q.pop();

        topologicalOrdering.push_back(u);

        const std::vector<Vertex> & adj = G.getAdj(u);
        for (Vertex v : adj) {

            // Decrement in-degree of adjacent vertex
            --inDegree[v];

            // Enqueue the vertex with 0 in-degree
            if (inDegree[v] == 0) 
                Q.push(v);          
        }
    }

    if (Vertex(topologicalOrdering.size()) != V) {
        std::cout << err << "\n";
        return;
    }

    for (int u : topologicalOrdering) {
        std::cout << u << ' ';
    }
    std::cout << "\n";
}