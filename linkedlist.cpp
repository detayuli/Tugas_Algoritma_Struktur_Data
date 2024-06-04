#include <iostream>
#include <vector>

using namespace std;

// Fungsi untuk menambahkan edge pada graph (Directed Graph)
void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
}

// Fungsi untuk menampilkan graph
void printGraph(const vector<vector<int>>& adj) {
    int V = adj.size();
    for (int u = 0; u < V; ++u) {
        cout << "Node " << u << " terhubung ke: ";
        for (int v : adj[u]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    int V = 4; // Jumlah simpul (vertices)

    // Inisialisasi adjacency list
    vector<vector<int>> adj(V);

    // Menambahkan edge pada graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 0);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 3);

    // Menampilkan graph
    printGraph(adj);

    return 0;
}
