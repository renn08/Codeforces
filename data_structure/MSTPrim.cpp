#include <climits>
#include <iostream>
#include <cstdlib>

#define V 5

using namespace std;

int minKey(int key[], bool mstSet[]) {
   int min = INT_MAX, min_index;
   
   for (int v = 0; v < V; v++)
       if (mstSet[v] == false && key[v] < min)
           min = key[v], min_index = v;
   
   return min_index;
}

void printMST(int parent[], int graph[V][V], char letters[]) {
   cout << "Minimum Spanning Tree:\n";
   for (int i = 1; i < V; i++)
       cout << letters[parent[i]] << " - " << letters[i] << " \tWeight: " << graph[i][parent[i]] << endl;
}

void primMST(int graph[V][V], char letters[]) {
   int parent[V];
   int key[V];
   bool mstSet[V];
   
   for (int i = 0; i < V; i++)
       key[i] = INT_MAX, mstSet[i] = false;
   
   key[0] = 0;
   parent[0] = -1;
   
   for (int count = 0; count < V - 1; count++) {
       int u = minKey(key, mstSet);
       mstSet[u] = true;
       
       for (int v = 0; v < V; v++)
           if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
               parent[v] = u, key[v] = graph[u][v];
   }
   
   printMST(parent, graph, letters);
}

int dist(const vector<int>& p1, const vector<int>& p2) { // any kind of dist calculation
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

int PrimMy(vector<vector<int>>& points) { 
    // points here is a vector of vector of x-y coordinates
   int n = points.size();
   vector<bool> visited(n, false);
   vector<int> key(n, INT_MAX);  // it's like using a memo to
   // to keep track of the outer node's min-weight path to
   // MST included nodes.
   // construct adj list
   vector<vector<int>> adjList(n, vector<int>(n, -1));
   for (int i = 0; i < n; ++i) {  // small at first
       for (int j = 0; j < n; ++j) {
           if (j > i)
               adjList[i][j] = dist(points[i], points[j]);
           else
               adjList[i][j] = adjList[j][i];
       }
   }
   int res = 0;
   int count = 0;  // num of included vertex
   // make start point key as 0
   key[0] = 0;
   visited[0] = true;
   count++;
   for (int i = 1; i < n; ++i) {
       key[i] = min(adjList[0][i], key[i]);
   }
   while (count != n) {
       // find the smallest key outside of visited
       int minIdx = 0;
       int minWeight = INT_MAX;
       for (int i = 0; i < n; ++i) {
           if (visited[i]) continue;
           if (key[i] < minWeight) {
               minIdx = i;
               minWeight = key[i];
           }
       }
       // put it into the visited
       visited[minIdx] = true;
       count++;
       res += minWeight;
       // for all adj node for that newly added node update key
       // so that key reflect min-weight path to connect to one
       // of the node in the visited set for each outside node.
       // then we just find the smallest one in these candidate
       // next included nodes.
       for (int i = 0; i < n; ++i) {
           if (i == minIdx) continue;
           if (adjList[minIdx][i] < key[i]) {
               key[i] = adjList[minIdx][i];
           }
       }
   }

   return res;
}

int main() {
   char letters[V] = {'A', 'B', 'C', 'D', 'E'};
   int graph[V][V] = {{0, 2, 0, 6, 0},
                      {2, 0, 3, 8, 5},
                      {0, 3, 0, 0, 7},
                      {6, 8, 0, 0, 9},
                      {0, 5, 7, 9, 0}};

   primMST(graph, letters);

   return 0;
}