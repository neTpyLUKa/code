#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
    int weight, v1, v2;
};

bool operator<(edge lhs, edge rhs) {
    return lhs.weight < rhs.weight;
}

int main() {
    int n_vertex, n_edges;
    std::cin >> n_vertex >> n_edges;
    std::vector<edge> graph(n_edges);
    for (int i = 0; i < n_edges; ++i) {
        int v1, v2, weight;
        std::cin >> v1 >> v2 >> weight;
        graph[i] = {weight, v1, v2};
    }
    std::sort(graph.begin(), graph.end());
    int cost = 0;
    std::vector<std::pair<int, int>> res;
    std::vector<int> tree_id(n_vertex + 1);
    for (int i = 1; i <= n_vertex; ++i) {
        tree_id[i] = i;
    }
    for (int i = 0; i < n_edges; ++i) {
        int v1 = graph[i].v1, v2 = graph[i].v2, len = graph[i].weight;
        //  std::cout << a << ' ' << b << '\n';
        if (tree_id[v1] != tree_id[v2]) {
            cost += len;
            res.push_back(std::make_pair(v1, v2));
            int old_id = tree_id[v2], new_id = tree_id[v1];
            for (int j = 1; j <= n_vertex; ++j) {
                if (tree_id[j] == old_id) {
                    tree_id[j] = new_id;
                }
            }
        }
    }
    std::cout << cost << '\n';
    return 0;
}
