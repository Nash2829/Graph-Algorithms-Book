// floydWarshall.cpp

#include "graph.hpp"
using ll = long long int;
const ll INF = 0x3f3f3f3f3f3f3f3f;

/**
 * @brief Finds the lengths of shortest paths between 
 * all pair of vertices using Floyd-Warshall's algorithm.
 * Prints "Graph has a negative cycle" if a negative cycle 
 * exists.
 * 
 * @param G The weighted Graph object G.
 * @return std::vector<std::vector<ll>> A vector of vectors
 * container storing the result. d[0][0] = 0 if graph has a 
 * negative cycle, otherwise 1.
 */
std::vector<std::vector<ll>> 
floydWarshall(const weightedGraph &G) {
    
    // Number of vertices
    int V = G.getV(); 

    // initialize d[i][j] to INF 
	std::vector<std::vector<ll>> 
        d(V + 1, std::vector<ll> (V + 1, INF));
    
    for (Vertex i = 1; i <= V; ++i)
        d[i][i] = 0LL;

    // If there is an edge between i and j,
    // set d[i][j] = weight
    for (Vertex u = 1; u <= V; ++u) {
        const std::vector<Edge>& adj = G.getAdj(u);
        for (Edge e : adj) {
            d[u][e.first] = std::min(d[u][e.first], 
                                     (ll)e.second);
        }
    }
    
    for (Vertex n = 1; n <= V; ++n) {
        for (Vertex i = 1; i <= V; ++i) {
            for (Vertex j = 1; j <= V; ++j) {
                d[i][j] = std::min(d[i][j], 
                                   (d[i][n] + d[n][j]));
            }
         }
    }
    
    for (Vertex u = 1; u <= V; ++u) {
        if (d[u][u] < 0) {
            std::cout << "Graph has a negative cycle\n";
            d[0][0] = 0;
            return d;
        }
    }
    d[0][0] = 1;
    return d;
}