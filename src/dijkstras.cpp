#include "dijkstras.h"


struct Node {
    int vertex;
    int weight;
    
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
	int n = G.numVertices;
	std::vector<int> distance(n, INF);
	std::vector<bool> visited(n, false);
	std::priority_queue<Node, std::vector<Node>, greater<Node>> pq;

	distance[source] = 0;
    pq.push({source, 0});

	while (!pq.empty()) {
		Node current = pq.top();
		pq.pop();
        int u = current.vertex;

		if (visited[u]) continue;
        visited[u] = true;

		for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({v, distance[v]});
            }
        }
	}
	return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances /*distances*/, const vector<int>& previous, int destination) {
	std::vector<int> path;
    if (distances[destination] == INF) return path;
    
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
	 if (v.empty()) {
        cout << "No path found." << endl;
        return;
    }
    
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}





