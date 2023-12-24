//
// Created by tim on 16.11.23.
//

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

template <typename T>
class Graph {
 private:
  T number_of_nodes_;
  std::vector<T> dist_;
  std::vector<std::vector<std::pair<T, T>>> adjacency_matrix_;

 public:
  Graph(T number_of_nodes) {
    adjacency_matrix_ =
        std::vector<std::vector<std::pair<T, T>>>(number_of_nodes);
    dist_ = std::vector<T>(number_of_nodes, std::numeric_limits<T>::max());
    number_of_nodes_ = number_of_nodes;
  }
  void AddEdge(T in_vertex, T weight1, T weight2) {
    T out_vertex1 = (in_vertex + 1) % number_of_nodes_;
    T out_vertex2 = (in_vertex * in_vertex + 1) % number_of_nodes_;
    adjacency_matrix_[in_vertex].push_back(
        std::make_pair(out_vertex1, weight1));
    adjacency_matrix_[in_vertex].push_back(
        std::make_pair(out_vertex2, weight2));
  }

  std::vector<T> Dijkstra(T start_node) {
    std::priority_queue<std::pair<T, T>, std::vector<std::pair<T, T>>,
                        std::greater<std::pair<T, T>>>
        traversal_queue;
    dist_[start_node] = 0;
    traversal_queue.push(std::make_pair(dist_[start_node], start_node));
    while (!traversal_queue.empty()) {
      std::pair<T, T> node = traversal_queue.top();
      traversal_queue.pop();
      for (std::uint64_t i = 0; i < adjacency_matrix_[node.second].size();
           i++) {
        T dist = node.first + adjacency_matrix_[node.second][i].second;
        if (dist < dist_[adjacency_matrix_[node.second][i].first]) {
          dist_[adjacency_matrix_[node.second][i].first] = dist;
          traversal_queue.push(
              std::make_pair(dist, adjacency_matrix_[node.second][i].first));
        }
      }
    }

    return dist_;
  }
};

int main() {
  std::int64_t weight1, weight2, number_of_nodes, start_node, end_node;
  std::cin >> weight1 >> weight2 >> number_of_nodes >> start_node >> end_node;
  Graph<std::int64_t> graph(number_of_nodes);
  for (std::int64_t i = 0; i < number_of_nodes; i++) {
    graph.AddEdge(i, weight1, weight2);
  }
  std::vector<std::int64_t> res = graph.Dijkstra(start_node);
  std::cout << res[end_node] << '\n';
  return 0;
}
