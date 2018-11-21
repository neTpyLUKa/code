#include <iostream>
#include <vector>

void dfs(const std::vector<std::vector<int>> &graph,
         std::vector<bool> &visited, int cur_vertex) {
    for (size_t i = 0; i < graph[cur_vertex].size(); ++i) {
        if (!visited[graph[cur_vertex][i]]) {
        visited[graph[cur_vertex][i]] = true;
        dfs(graph, visited, graph[cur_vertex][i]);
        }
    }
}

int main() {
    int n_vertex, n_edges;
    std::cin >> n_vertex >> n_edges;
    std::vector<std::vector<int>> graph(n_vertex, std::vector<int>(0));
    for (int i = 0; i < n_edges; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    std::vector<bool> visited(n_vertex);
    visited[0] = true;
    dfs(graph, visited, 0);
    int n = 0;
    for (int i = 0; i < n_vertex; ++i) {
        if (visited[i]) {
        ++n;
        }
    }
    std::cout << n << "\n";
    for (int i = 0; i < n_vertex; ++i) {
        if (visited[i]) {
        std::cout << i + 1 << " ";
        }
    }
}

