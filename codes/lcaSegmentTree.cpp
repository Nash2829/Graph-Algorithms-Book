// lcaSegmentTree.cpp

#include <vector>
#include <algorithm>

struct LCA {
    const int INF = 0x3f3f3f3f;
    std::vector<int> depth, euler, firstFoundAt, segTree;
    std::vector<bool> visited;
    int V, segTreeSize;

    LCA(std::vector<std::vector<int>> &adj, int root = 1) :
        V(int(adj.size())),
        depth(std::vector<int>(V + 1)),
        firstFoundAt(std::vector<int>(V + 1)),
        visited(std::vector<bool>(V + 1)) {

        euler.reserve(2 * V);
        depth[root] = -1;
        eulerTourDFS(adj, root, root);
        depth[0] = INF;
        int m = euler.size(), sz;
        for (sz = 1; sz < m; sz <<= 1);
        segTree.resize(sz << 1);
            
        for (int i = 0; i < m; ++i) 
            segTree[sz + i] = euler[i];
            
        for (int i = sz - 1; i >= 1; --i) {
            int l = segTree[i << 1], r = segTree[i << 1 | 1];
            segTree[i] = (depth[l] > depth[r] ? r : l);
        }
        segTreeSize = sz << 1;
    }

    void eulerTourDFS(std::vector<std::vector<int>> &adj, int u, int parent) {
        visited[u] = true;
        depth[u] = depth[parent] + 1;
        firstFoundAt[u] = int(euler.size());
        euler.push_back(u);
        for (int v : adj[u]) {
            if (not visited[v]) {
                eulerTourDFS(adj, v, u);
                euler.push_back(u);
            }
        }
    }

    int query(int L, int R, int l = 0, int r = - 1, int v = 1)
    {
        if (r == -1) 
            r += segTreeSize;
        if (R < l or L > r) 
            return 0;
        if (L <= l and R >= r) 
            return segTree[v];
        int mid = l + ((r - l) >> 1);
        int left = query(L, R, l, mid, v << 1);
        int right = query(L, R, mid + 1, r, v << 1 | 1);
        return (depth[left] > depth[right] ? right : left);
    }

    int lca(int u, int v) {
        int l = firstFoundAt[u];
        int r = firstFoundAt[v];
        if (l > r) 
            std::swap(l, r);
        return query(l, r);
    }    
};

int main() {}