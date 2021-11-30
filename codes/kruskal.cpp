// kruskal.cpp

#include<vector>
#include<algorithm>

struct Edge {
    int u, v, weight;    
    Edge(int a, int b, int w) : 
        u(a), v(b), weight(w) {}
    bool operator<(const Edge& other) const {
        return (weight < other.weight);
    }
};

struct DisjointSetUnion {
    int n;
    int *parent, *size;
    DisjointSetUnion(int _n) : n(_n) {
        parent = new int[n + 1]();
        size = new int[n + 1]();
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    /**
     * @brief Finds the parent of the set containing vertex v 
     * with path compression.
     * 
     * @param v The vertex whose parent set is to be found.
     * @return int The parent of the set containing v.
     */
    int findSet(int v) {
        if (v == parent[v])
            return v;
        parent[v] = findSet(parent[v]);
        return parent[v];
    }

    /**
     * @brief Unions two sets containing a and b.
     * Calls the findSet function.
     * 
     * @param a The vertex a
     * @param b The vertex b
     * @return true Returns true if a union was done.
     * @return false Returns false if no union was done,
     * i.e., params a and b already belonged to the same
     * set.
     */
    bool unionSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (size[a] < size[b]) 
                std::swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            size[b] = 0;
            return true;
        }
        return false;
    }
};

/**
 * @brief Solves the problem of minimum spanning tree 
 * using Kruskal's algorithm.
 * 
 * @param edges Container of edges.
 * @param V Number of vertices.
 * @return long long int The sum of all the weights in the minimum spanning tree. 
 */
long long int
kruskalMST(std::vector<Edge> edges, int V) {
    std::sort(edges.begin(), edges.end());
    long long int sumMST = 0LL;
    DisjointSetUnion dsu(V); 
    for (Edge e : edges) {
        if (dsu.unionSets(e.u, e.v)) {
            sumMST += 1LL * e.weight;
        }   
    }
    return sumMST;
}