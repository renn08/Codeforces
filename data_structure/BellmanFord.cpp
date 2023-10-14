// To solve single source shortest path with any weight (possibly negative weight)
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;


// Bellman-Ford classical is just dp with memo optimized to 2*n (we can use % 2 here)
// TODO: MUST READ: adjList here is if directed graph, vertex pointed to is 1st dim of adjList
class DP { // cannot detect negative weight cycle, in this case, produce wrong result
// given the shortest path between any two vertex at most have V - 1 edges.
// we can find from source vertex, every vertex's shortest distance from source
// using exactly i edges, 0 <= i <= V - 1, this can use dynamic programming:
// state: vertex idx j, the min distance from source using i edges. (inf if impossible)
// state vars: i, j
// recurrence relationship: f(i, j) = min(f(i - 1, k) + weight of edge connect k and j), here k should be connected to j. Update dist (shortest distance) along
// the way
public:
    DP(int n, vector<vector<pair<int, int> > >& adjList) {
        this->n = n;  // size
        this->adjList = adjList;
        this->dist.resize(n, INT_MAX);
        this->shortestPathEdgeNum.resize(n, 0);
        this->memo.resize(n);
        for (auto& vec : memo) {
            vec.resize(n, INT_MAX);
        }
        this->parentMemo.resize(n);
        for (auto& vec : parentMemo) {
            vec.resize(n, -1);
        }
    }

    void dp(int source) { // O(2VE)
        // base case
        memo[0][source] = 0; // for other vertex cannot use 0 edge to go to source
        // so all inf
        dist[source] = 0;

        for (int i = 1; i < n; ++i) {
            // Indeed we can detect negative weight cycle by iterating on the nth
            // number of edges, since if positive weight cycle, at most n - 1 edges
            // for shortest path, so as long as we detect minDist update on nth
            // edge, we find there exist negative weight cycle
            for (int j = 0; j < n; ++j) { // V
                int minDist = INT_MAX;
                int minParent = -1;
                for (int k = 0; k < adjList[j].size(); ++k) { // every edge will be 
                // visited by two vertex (its sides) for V time (0 ~ V - 1 edges), so in total inner
                // two loop cost O(2VE)
                    auto& p = adjList[j][k];
                    int w = p.second;
                    int v = p.first;
                    if (memo[i - 1][v] == INT_MAX) continue;
                    if (minDist > memo[i - 1][v] + w) {
                        minDist = memo[i - 1][v] + w;
                        minParent = v;
                    }
                }
                memo[i][j] = minDist;
                parentMemo[i][j] = minParent;
                if (dist[j] > memo[i][j]) {
                    dist[j] = memo[i][j];
                    shortestPathEdgeNum[j] = i;
                }
            }
        }
    }

    void printPath(int v) {
        // print
        if (dist[v] == INT_MAX) {
            cout << "no path to source" << endl;
        }
        cout << "The shortest path weight to source from " << v
             << " is:" << dist[v] << endl;

        int spen = shortestPathEdgeNum[v];

        stack<int> path;
        int parentV = parentMemo[spen--][v];
        path.emplace(v);

        while (spen != -1) {
            path.emplace(parentV);
            v = parentV;
            parentV = parentMemo[spen--][v];
        }

        cout << "The shortest path: " << path.top();
        path.pop();
        while (!path.empty()) {
            cout << "->" << path.top();
            path.pop();
        }
        cout << endl;
    }

private:
    vector<vector<pair<int, int> > > adjList; // if directed should be in edge
    int n; // size
    vector<int> dist; // shortest distance for each vertex
    vector<int> shortestPathEdgeNum;
    vector<vector<int> > memo;
    vector<vector<int> > parentMemo;
};

class BellmanFord {
private:

public:
};

int main() {
    // all positive weight example
    vector<vector<pair<int, int> > > adjList = {{{1, 5}, {2, 8}},
                                                {{0, 5}, {3, 2}, {2, 9}},
                                                {{0, 8}, {1, 9}, {3, 6}},
                                                {{1, 2}, {2, 6}}};
    DP d(4, adjList);
    d.dp(0);
    d.printPath(3);

    // negative weight but positive weight cycle example
    vector<vector<pair<int, int> > > adjList1 = {{},
                                                {{0, 100}, {3, -150}},
                                                {{0, 500}, {1, 100}},
                                                {{0, 200}, {2, 100}}};
    DP d1(4, adjList1);
    d1.dp(0);
    d1.printPath(1);
    return 0;
}