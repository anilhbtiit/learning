// C++ Code for Topological Sorting using different algorithms
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

// Class to represent a graph
class Graph {
private:
    int V;                        // Number of vertices
    vector<vector<int>> adjList;  // Adjacency list representation

    // Utility function for DFS-based Topological Sort
    void dfsUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited, Stack);
            }
        }

        Stack.push(v);
    }

public:
    Graph(int V) : V(V), adjList(V) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // Topological Sort using DFS
    void topologicalSortDFS() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsUtil(i, visited, Stack);
            }
        }

        cout << "Topological Sort (DFS): ";
        while (!Stack.empty()) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
        cout << endl;
    }

    // Topological Sort using Kahn's Algorithm
    void topologicalSortKahns() {
        vector<int> inDegree(V, 0);

        for (int i = 0; i < V; i++) {
            for (int neighbor : adjList[i]) {
                inDegree[neighbor]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topoOrder;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            topoOrder.push_back(curr);

            for (int neighbor : adjList[curr]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        cout << "Topological Sort (Kahn's): ";
        for (int node : topoOrder) {
            cout << node << " ";
        }
        cout << endl;
    }

    // Topological Sort using Source Removal
    void topologicalSortSourceRemoval() {
        vector<int> inDegree(V, 0);
        for (int i = 0; i < V; i++) {
            for (int neighbor : adjList[i]) {
                inDegree[neighbor]++;
            }
        }

        vector<bool> removed(V, false);
        vector<int> topoOrder;

        for (int count = 0; count < V; count++) {
            int source = -1;
            for (int i = 0; i < V; i++) {
                if (!removed[i] && inDegree[i] == 0) {
                    source = i;
                    break;
                }
            }

            if (source == -1) {
                cout << "Graph contains a cycle, no topological sort possible." << endl;
                return;
            }

            removed[source] = true;
            topoOrder.push_back(source);

            for (int neighbor : adjList[source]) {
                inDegree[neighbor]--;
            }
        }

        cout << "Topological Sort (Source Removal): ";
        for (int node : topoOrder) {
            cout << node << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Using different algorithms for Topological Sort on a DAG:\n";

    g.topologicalSortDFS();
    g.topologicalSortKahns();
    g.topologicalSortSourceRemoval();

    return 0;
}

