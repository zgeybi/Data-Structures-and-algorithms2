//
// Created by tim on 19.11.23.
//

#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

template <typename T>
class Graph {
 private:
  T number_of_nodes_;
  std::vector<std::vector<std::pair<T, T>>> adjacency_list_;

 public:
  Graph(T number_of_nodes) {
    adjacency_list_ =
        std::vector<std::vector<std::pair<T, T>>>(number_of_nodes + 1);
    number_of_nodes_ = number_of_nodes;
  }
  void AddEdge(T in_vertex, T out_vertex, T weight) {
    adjacency_list_[in_vertex].push_back(std::make_pair(weight, out_vertex));
  }
  T FindCheapestPrice(T start_node, T end_node, T number_of_flights) {
    std::priority_queue<std::pair<T, T>, std::vector<std::pair<T, T>>,
                        std::greater<std::pair<T, T>>>
        traversal_queue;
    traversal_queue.push({0, start_node});
    std::vector<T> min_cost(number_of_nodes_ + 1,
                            std::numeric_limits<T>::max());
    min_cost[start_node] = 0;
    T stops = 0;
    while (!traversal_queue.empty() && stops < number_of_flights) {
      uint32_t size = traversal_queue.size();
      while (size-- != 0) {
        auto [cost, current_node] = traversal_queue.top();
        traversal_queue.pop();
        for (auto& [price, neighbour] : adjacency_list_[current_node]) {
          if (price + cost < min_cost[neighbour]) {
            min_cost[neighbour] = price + cost;
            traversal_queue.push(
                std::make_pair(min_cost[neighbour], neighbour));
          }
        }
      }
      stops++;
    }
    if (stops - 1 >= number_of_flights) {
      return -1;
    }
    if (min_cost[end_node] >= std::numeric_limits<T>::max()) {
      return -1;
    }
    return min_cost[end_node];
  }
};

int main() {
  std::int64_t number_of_nodes, number_of_edges, number_of_flights, start_node,
      end_node;
  std::cin >> number_of_nodes >> number_of_edges >> number_of_flights >>
      start_node >> end_node;
  Graph<std::int64_t> graph(number_of_nodes);

  for (int i = 0; i < number_of_edges; i++) {
    std::int64_t temp_in_vertex, temp_out_vertex, temp_weight;
    std::cin >> temp_in_vertex >> temp_out_vertex >> temp_weight;
    graph.AddEdge(temp_in_vertex, temp_out_vertex, temp_weight);
  }
  std::cout << graph.FindCheapestPrice(start_node, end_node, number_of_flights)
            << '\n';
  return 0;
}