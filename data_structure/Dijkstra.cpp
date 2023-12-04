#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

// #define SIZE 100000 + 1

class Dijkstra {
public:
    Dijkstra(int n, vector<vector<pair<int, int> > >& adjList) {
        this->adjList = adjList;
        this->dist.resize(n, INT_MAX);
        this->vis.resize(n, false);
        this->parent.resize(n, -1);
        this->n = n;
    }

    void reset() {
        this->dist.resize(n, INT_MAX);
        this->vis.resize(n, false);
        this->parent.resize(n, -1);
    }

    void dijkstra(int source) {
        dist[source] = 0;
        multiset<pair<int, int> > s; // multiset do the job as the min pq.

        s.emplace(0, source); // source node with dist = 0

        while (!s.empty()) {
            pair<int, int> p = *s.begin(); // pop the vertex with the min dist
            s.erase(s.begin()); // poped out means already optimal

            int w = p.first; // weight
            int i = p.second; // idx
            if (vis[i]) continue; // skip if has visited
            vis[i] = true;
            
            for (int j = 0; j < adjList[i].size(); ++j) { // check all connected node and update and push to pq if update successfully
                int v = adjList[i][j].first; // vertex index
                int vw = adjList[i][j].second; // edge weight
                if (dist[i] + vw < dist[v]) {
                    dist[v] = dist[i] + vw;
                    parent[v] = i;
                    s.emplace(dist[v], v);
                }
            }
        }
    }

    void printPath(int v) {
        if (dist[v] == INT_MAX) {
            cout << "no path to source" << endl;
        }
        cout << "The shortest path weight to source from " << v
             << " is:" << dist[v] << endl;

        stack<int> path;
        int parentV = parent[v];
        path.emplace(v);

        while (parentV != -1) {
            path.emplace(parentV);
            v = parentV;
            parentV = parent[v];
        }

        cout << "The shortest path: " << path.top();
        path.pop();
        while (!path.empty()) {
            cout << "->" << path.top();
            path.pop();
        }
    }

private:
    vector<vector<pair<int, int> > > adjList;  // each vertex has all its connected
    // vertex with edge weighted (pair: vertex idx, weight)
    vector<int> dist;  // vertex min dist to source
    vector<bool> vis;  // visited or not
    vector<int> parent;
    int n = 0; // size of vertex
};

int main() {
    vector<vector<pair<int, int> > > adjList = {{{1, 5}, {2, 8}}, {{0, 5}, {3, 2},{2, 9}}, {{0, 8}, {1, 9}, {3, 6}}, {{1, 2}, {2, 6}}};
    Dijkstra d(4, adjList);
    d.dijkstra(0);
    d.printPath(3);
    return 0;
}