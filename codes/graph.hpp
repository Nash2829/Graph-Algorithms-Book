#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using Vertex = int;
using Edge = std::pair<Vertex, Vertex>; // first stores vertex and second stores the edge weight

class weightedGraph {

    protected:
        /**
         * Number of Vertices.
         * 
         */
        Vertex V;

        /**
         * Adjacency list representation.
         * 
         */
        std::vector<Edge> *adj;

        /**
         * Directed or undirected graph.
         * 
         */
        bool directed;

    public:

        /**
         * @brief Constructs a new weighted Graph object.
         * 
         * @param _V number of vertices in the graph.
         * @param _directed default value = false. specify as true if the graph is directed.
         */
        weightedGraph(Vertex _V, bool _directed = false) : V(_V), directed(_directed) {
            adj = new std::vector<Edge> [V + 1](); // 1-based indexing for vertices
        }

        /**
         * @brief Constructs a new weighted Graph object. It is a copy of an old one.
         * 
         * @param copy the old weighted Graph object to be copied.
         */
        weightedGraph(const weightedGraph &copy) : V(copy.V), directed(copy.directed) {
            adj = new std::vector<Edge> [V + 1]();
            for (Vertex i = 0; i <= V; ++i) {
                adj[i] = copy.adj[i];
            }
        }

        /**
         * @brief Destroys the weighted Graph object.
         * 
         */
        virtual ~weightedGraph() {
            delete []adj;
        }

        /**
         * @brief adds an edge from vertex u to v. If directed is false, also adds an edge 
         *        from v to u.
         * @param u vertex from which edge comes out.
         * @param v vertex to which edge comes in.
         * @param weight the weight of the edge.
         */
        void addEgde(Vertex u, Vertex v, Vertex weight) {
            adj[u].push_back(Edge(v, weight));
            if (not directed) 
                adj[v].push_back(Edge(u, weight));
        }
};

class Graph {

    protected:
        /**
         * Number of Vertices.
         * 
         */
        Vertex V;

        /**
         * Adjacency list representation.
         * 
         */
        std::vector<Vertex> *adj;

        /**
         * Directed or undirected graph.
         * 
         */
        bool directed;

    public:

        /**
         * @brief Constructs a new Graph object.
         * 
         * @param _V number of vertices in the graph.
         * @param _directed default value = false. Specify as true if the graph is directed
         */
        Graph(Vertex _V, bool _directed = false) : V(_V), directed(_directed) {
            adj = new std::vector<Vertex> [V + 1](); // 1-based indexing for vertices
        }

        /**
         * @brief Constructs a new Graph object. It is a copy of an old one.
         * 
         * @param copy the old Graph object to be copied.
         */
        Graph(const Graph &copy) : V(copy.V), directed(copy.directed) {
            adj = new std::vector<Vertex> [V + 1]();
            for (Vertex i = 0; i <= V; ++i) {
                adj[i] = copy.adj[i];
            }
        }

        /**
         * @brief Destroys the Graph object.
         * 
         */
        virtual ~Graph() {
            delete []adj;
        }

        /**
         * @brief adds an edge from vertex u to v. If directed is false, also adds an edge 
         *        from v to u.
         * @param u vertex from which edge comes out.
         * @param v vertex to which edge comes in.
         */
        void addEgde(Vertex u, Vertex v) {
            adj[u].push_back(v);
            if (not directed) 
                adj[v].push_back(u);
        }
};

#endif
