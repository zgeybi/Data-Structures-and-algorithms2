//
// Created by tim on 20.11.23.
//

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

template <typename T, typename D>
class Graph {
 private:
  T number_of_nodes_;
  std::vector<std::vector<std::pair<D, T>>> adjacency_list_;

 public:
  Graph(T number_of_nodes) {
    adjacency_list_ =
        std::vector<std::vector<std::pair<D, T>>>(number_of_nodes + 1);
    number_of_nodes_ = number_of_nodes;
  }
  void AddEdge(T in_vertex, T out_vertex, D weight) {
    adjacency_list_[in_vertex].push_back(std::make_pair(weight, out_vertex));
    adjacency_list_[out_vertex].push_back(std::make_pair(weight, in_vertex));
  }
  D Dijkstra(T start_node, T end_node) {
    std::priority_queue<std::pair<D, T>, std::vector<std::pair<D, T>>,
                        std::greater<std::pair<D, T>>>
        traversal_queue;
    std::vector<D> cost(number_of_nodes_ + 1, std::numeric_limits<D>::max());
    cost[start_node] = 0;
    traversal_queue.push(std::make_pair(0, start_node));
    while (!traversal_queue.empty()) {
      auto [price, current_node] = traversal_queue.top();
      traversal_queue.pop();
      for (auto& [neighbor_price, neighbor_node] :
           adjacency_list_[current_node]) {
        if (cost[current_node] + neighbor_price -
                cost[current_node] * neighbor_price <
            cost[neighbor_node]) {
          cost[neighbor_node] = cost[current_node] + neighbor_price -
                                cost[current_node] * neighbor_price;
          traversal_queue.push(
              std::make_pair(cost[neighbor_node], neighbor_node));
        }
      }
    }
    return cost[end_node];
  }
};
int main() {
  std::uint64_t number_of_nodes, number_of_edges, start_node, end_node;
  std::cin >> number_of_nodes >> number_of_edges >> start_node >> end_node;
  Graph<std::uint64_t, double> graph(number_of_nodes);
  for (std::uint64_t i = 0; i < number_of_edges; i++) {
    double temp_weight;
    std::uint64_t temp_in_vertex, temp_out_vertex;
    std::cin >> temp_in_vertex >> temp_out_vertex >> temp_weight;
    graph.AddEdge(temp_in_vertex, temp_out_vertex, temp_weight / 100);
  }

  std::cout << std::setprecision(2);
  std::cout << std::noshowpoint << graph.Dijkstra(start_node, end_node);

  return 0;
}
