// optimized unionfind with fast union, rank and path compression
#include<vector>
#include<iostream>

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

int main() {
    UnionFind unionFind(10);
    return 1;
}