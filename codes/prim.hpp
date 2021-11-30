// prim.hpp

#ifndef PRIM_HPP
#define PRIM_HPP

#include "graph.hpp"

struct Prim : public weightedGraph {
    const long long int INF = 0x3f3f3f3f3f3f3f3f;

    /**
     * @brief Constructs a new Prim object.
     * 
     * @param _V Number of vertices.
     * @param _directed Default = false. specify true if graph is directed.
     */
    Prim(Vertex _V, bool _directed = false) : 
        weightedGraph(_V, _directed) {}

    /**
     * @brief Constructs a new Prim object from a weighted Graph object.
     * 
     * @param G The weighted Graph Object to be copied.
     */
    Prim(weightedGraph G) : weightedGraph(G) {}

    /**
     * @brief Constructs a new Prim object from an old one. 
     * It calls the weightedGraph copy constructor.
     * 
     * @param copy The old Prim object to be copied.
     */
    Prim(const Prim &copy) : weightedGraph(copy) {}
    
    /**
     * @brief Solves the problem of minimum spanning tree using Prim's 
     * algorithm.
     * 
     * @return ll The sum of all the weights in the minimum spanning tree. 
     */
    long long int PrimMST() {
        long long int sumMST = 0LL;
        int weightCount = 0;
        std::vector<bool> visited(V + 1);
        std::priority_queue<Edge, std::vector<Edge>, 
                                    std::greater<Edge>> pQ;

        // first - Edge weight.
        // second - Vertex. 
        pQ.push(Edge(0, 1));

        while (not pQ.empty()) {
            Edge E = pQ.top();
            pQ.pop();
            Vertex u = E.second;
            if (visited[u])
                continue;
            visited[u] = true;
            sumMST += 1LL * E.first;
            weightCount++;
            if (weightCount == V) 
                break;
            for (Edge e : adj[u]) {
                int v = e.first;
                if (visited[v])
                    continue;
                pQ.push(Edge(e.second, v));
            }
        }

        return sumMST;
    }
};

#endif