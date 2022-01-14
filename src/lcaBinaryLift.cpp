// lcaBinaryLift.cpp

#include <vector>
#include <algorithm>

struct LCA {
    int timer, L, V;
    std::vector<int> tin, tout;
    std::vector<std::vector<int>> ancestor;

    LCA(std::vector<std::vector<int>> &adj, int _V, int root = 1) :
    	timer(0),
        V(_V),
        tin(std::vector<int>(V + 1)),
    	tout(std::vector<int>(V + 1)) {

      	for (L = 1; L < V; L <<= 1); // L = ceil(log V)
		ancestor.assign(V + 1, std::vector<int>(L + 1));
        dfs(adj, root, root);
    }

    void dfs(std::vector<std::vector<int>> &adj, int u, int parent) {
        tin[u] = ++timer;
        ancestor[u][0] = parent;
        for (int i = 1; i <= L; ++i)
            ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
        for (int v : adj[u]) {
            if (v != parent) {
                dfs(adj, v, u);
            }
        }
        tout[u] = ++timer;
    }

    bool isAncestor(int u, int v) {
        return (tin[u] <= tin[v] and tout[u] >= tout[v]);
    }
    
    int lca(int u, int v)
    {
        if (isAncestor(u, v))
            return u;
       	if (isAncestor(v, u))
            return v;
        for (int i = L; i >= 0; --i) {
            if (not isAncestor(ancestor[u][i], v))
                u = ancestor[u][i];
        }
        return ancestor[u][0];
    }
};