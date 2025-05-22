#if 1
#include <iostream>
#include <vector>
#include <queue>

// Function to perform topological sort
std::vector<int> topologicalSort(int vertices, const std::vector<std::vector<int>>& adjList) {
    std::vector<int> inDegree(vertices, 0);
    std::vector<int> topoOrder;
    
    // Calculate in-degrees of all vertices
    for (int i = 0; i < vertices; ++i) {
        for (int neighbor : adjList[i]) {
            inDegree[neighbor]++;
        }
    }

    // Push all vertices with in-degree 0 into the queue
    std::queue<int> q;
    for (int i = 0; i < vertices; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // Process the vertices in topological order
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        topoOrder.push_back(current);

        // Decrease the in-degree of neighbors and enqueue if in-degree becomes 0
        for (int neighbor : adjList[current]) {
            if (--inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Check if the graph had a cycle
    if (topoOrder.size() != vertices) {
        throw std::runtime_error("Graph is not a DAG, topological sorting not possible.");
    }

    return topoOrder;
}

int main() {
    int vertices = 6; // Number of vertices in the graph
    std::vector<std::vector<int>> adjList(vertices);

    // Define the edges of the graph
    adjList[5].push_back(2);
    adjList[5].push_back(0);
    adjList[4].push_back(0);
    adjList[4].push_back(1);
    adjList[2].push_back(3);
    adjList[3].push_back(1);

    try {
        // Perform topological sort
        std::vector<int> topoOrder = topologicalSort(vertices, adjList);

        // Print the topological order
        std::cout << "Topological Order: ";
        for (int node : topoOrder) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


#else

#include <bits/stdc++.h>
using namespace std;

// Function to perform DFS and topological sorting
void topologicalSortUtil(int v, vector<vector<int> >& adj,
                         vector<bool>& visited,
                         stack<int>& Stack)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all adjacent vertices
    for (int i : adj[v]) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, Stack);
    }

    // Push current vertex to stack which stores the result
    Stack.push(v);
}

// Function to perform Topological Sort
void topologicalSort(vector<vector<int> >& adj, int V)
{
    stack<int> Stack; // Stack to store the result
    vector<bool> visited(V, false);

    // Call the recursive helper function to store
    // Topological Sort starting from all vertices one by
    // one
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, Stack);
    }

    // Print contents of stack
    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

int main()
{

    // Number of nodes
    int V = 4;

    // Edges
    vector<vector<int> > edges
        = { {1,2}, {3,1}, { 5, 1 }, { 3, 2 } };

    // Graph represented as an adjacency list
    vector<vector<int> > adj(V);

    for (auto i : edges) {
        adj[i[0]].push_back(i[1]);
    }

    cout << "Topological sorting of the graph: ";
    topologicalSort(adj, V);
    cout << "\n";

    return 0;
}
#endif
