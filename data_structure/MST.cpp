// Kruskal's algorithm is to find the mst in a graph, connected or disconnected
// 1. Sort all the edges in non-decreasing order of their weight
// 2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If the cycle is not formed, include that edge. Else, discard it.
// 3. Repeat 2. until V - 1 edges in the spanning tree

// optimized unionfind with fast union, rank and path compression
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
   public:
    UnionFind(int n) {      // n: the number of initial parts
        rank.resize(n, 0);  // initial height to be 0
        root.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x) {
        // return the root
        if (x == root[x]) {
            return x;
        }
        return root[x] = find(root[x]);
    }

    void unionset(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] > rank[rooty]) {
                root[rooty] = rootx;
            } else if (rank[rootx] < rank[rooty]) {
                root[rootx] = rooty;
            } else {
                root[rooty] = rootx;
                rank[rootx]++;
            }
        }
    }

    bool isConnected(int x, int y) { return find(x) == find(y); }

   private:
    vector<int> rank;
    vector<int> root;
};

class MST {
public:
    MST(int v) {
        this->v = v;
    }

    // add a edge
    void addEdge(int x, int y, int w) {
        edges.push_back({w, x, y});
    }

    void mstKruskal() {
        // sort all edges by weight non-decreasing
        sort(edges.begin(), edges.end());

        // detect cycle using UnionFind
        UnionFind u(v);
        int ans = 0;
        cout << "Following are the edges in the constructed MST" << endl;
        for (auto& e : edges) {
            // if are connected already and another e connect them then cycle detected
            if (u.find(e[1]) != u.find(e[2])) {
                u.unionset(e[1], e[2]);
                ans += e[0];
                cout << e[1] << " -- " << e[2] << " == " << e[0] << endl;
            }
        }
        cout << "MST cost: " << ans << endl;
    }

private:
    int v;
    vector<vector<int>> edges;
};

int main() {
    MST m(6);
    m.addEdge(0, 1, 10);
    m.addEdge(1, 3, 15);
    m.addEdge(2, 3, 4);
    m.addEdge(2, 0, 6);
    m.addEdge(0, 3, 5);
    m.addEdge(4, 5, 100);
    m.mstKruskal();
    return 0;
}
