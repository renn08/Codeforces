#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>

using namespace std;

class UnionFindWithWeight {
public:
    UnionFindWithWeight(int n) {      // n: the number of initial parts
        rank.resize(n, 0);  // initial height to be 0
        root.reserve(n);
        for (int i = 0; i < n; ++i) {
            root[i] = make_pair(i, 1);
        }
    }

    pair<int, double> find(int x) {
        // return a pair of rootid and this node weight with respect to the root
        if (x == root[x].first) {
            return root[x];
        }
        else { // chain update along the path from root to leaf
            pair<int, double> rootPair = find(root[x].first);
            root[x].second *= rootPair.second;
            root[x].first = rootPair.first;
        }
        return root[x];
    }

    void unionset(int x, int y, double q) {
        // special: if update two node's weight ratio within one set, the old ratio will be preserved.
        // suppose x is the dividend, and y is the divisor, then q = x/y
        // so update the joining root's weight to be 1 / joining node weight
        // with respect to its root(need find to determine) * be joined node
        // weight with respect to its root * (joining node weight/be joined node
        // weight, that is newly known, namely their quotient) union only update
        // weight of the root of each disjoint set, find will lazily update the
        // weight of node to found (and its root and root's parent) to their
        // real weight with respect to newest root
        pair<int, double> rootWeightX = find(x);
        pair<int, double> rootWeightY = find(y);
        int rootx = rootWeightX.first;
        int rooty = rootWeightY.first;
        double weightx = rootWeightX.second;
        double weighty = rootWeightY.second;
        if (rootx != rooty) {
            if (rank[rootx] > rank[rooty]) { // rooty joining to rootx
                root[rooty].first = rootx;
                root[rooty].second = 1 / weighty * weightx * 1 / q;
            } else if (rank[rootx] < rank[rooty]) { // rootx joining to rooty
                root[rootx].first = rooty;
                root[rootx].second = 1 / weightx * weighty * q;
            } else {
                root[rooty].first = rootx; // rooty joining to rootx
                root[rooty].second = 1 / weighty * weightx * 1 / q;
                rank[rootx]++;
            }
        }
    }

    bool isConnected(int x, int y) { return find(x).first == find(y).first; }

private:
    vector<int> rank;
    vector<pair<int, double>> root; // id->(rootid, weight) id map to its root and its weight
};

int main() {
    UnionFindWithWeight u(4);
    unordered_map<string, int> id;
    id.emplace("happy", 0);
    id.emplace("sad", 1);
    id.emplace("angry", 2);
    id.emplace("love", 3);

    u.unionset(0, 1, 2);
    u.unionset(2, 3, 3);
    u.unionset(1, 2, 1.5);
    pair<int, double> rootWeight1 = u.find(0);
    pair<int, double> rootWeight2 = u.find(3);
    cout << "Does happy and love belong to same set: " << (rootWeight1.first == rootWeight2.first) << endl;
    cout << "Their weight ratio (happy / love) is: " << rootWeight1.second / rootWeight2.second << endl;
    return 0;
}
