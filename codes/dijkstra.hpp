// dijkstra.hpp

#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "graph.hpp"

struct Dijkstra : public weightedGraph {
    using ll = long long int;
    const ll INF = 0x3f3f3f3f3f3f3f3f;

    ll *d;
    Vertex *p;

    /**
     * @brief Constructs a new Dijkstra object.
     * 
     * @param _V Number of vertices.
     * @param _directed Default = false. specify true if graph is directed.
     */
    Dijkstra(Vertex _V, bool _directed = false) : weightedGraph(_V, _directed) {
        d = new ll[V + 1]();
        p = new Vertex[V + 1]();
    }

    /**
     * @brief Constructs a new Dijkstra object from a weighted Graph object.
     * 
     * @param G The weighted Graph Object to be copied.
     */
    Dijkstra(weightedGraph G) : weightedGraph(G) {
        d = new ll[V + 1];
        p = new Vertex[V + 1]();
    }

    /**
     * @brief Constructs a new Dijkstra object from an old one. 
     * It calls the weightedGraph copy constructor.
     * 
     * @param copy The old Dijkstra object to be copied.
     */
    Dijkstra(const Dijkstra &copy) : weightedGraph(copy) {
        memcpy(d, copy.d, sizeof(ll) * (V + 1));
    }
    

    /**
     * @brief Destroys the Dijkstra object.
     * 
     */
    ~Dijkstra() {
        delete []d;
    }

    /**
     * @brief finds the lengths of shortest paths from the source vertex to all 
     * vertices and stores in Dijkstra::d[].
     * 
     * @param s Default = 1. The source vertex.
     */
    void solveShortestPaths(Vertex s = 1) {
        using length = std::pair<ll, Vertex>;
        std::priority_queue<length, std::vector<length>, std::greater<length>> 
                                                                            pq;
        memset(d, 0x3f, sizeof(ll) * (V + 1)); // initializing d[] to INF
        d[s] = 0LL;
        p[s] = -1;
        pq.push(length(d[s], s));
        while (not pq.empty()) {
            Vertex u = pq.top().second;
            ll dist = pq.top().first;
            pq.pop();

            if (dist > d[u])
                continue;

            for (Edge e : adj[u]) {
                auto[v, len] = e;
                if (len + d[u] < d[v]) {
                    d[v] = len + d[u];
                    p[v] = u;
                    pq.push(length(d[v], v));
                }
            }
        }
    }

    /**
     * @brief prints a path from start vertex s to destination vertex t. Also
     * returns a vector container having the path.
     * 
     * @param s Start vertex s.
     * @param t Destination vertex t.
     * @return std::vector<Vertex> Vector Container having the correct order 
     * of vertices in its path.
     */
    std::vector<Vertex> printPath(Vertex s, Vertex t) {
        std::vector<Vertex> path;
        path.reserve(V);
        for (Vertex u = t; u != s; u = p[u]) 
            path.push_back(u);
        path.push_back(s);
        std::reverse(path.begin(), path.end());
        for (int u : path) {
            std::cout << u << ' ';
        }
        std::cout << "\n";
        return path;
    }

};