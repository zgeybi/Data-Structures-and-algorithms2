//
// Created by tim on 10.11.23.
//

#include <cstdio>
#include <stack>
#include <vector>

class Graph {
 private:
  int number_of_nodes_;
  std::vector<std::vector<int>> graph_;
  std::vector<int> neighbor_degree_;

 public:
  Graph(std::vector<std::vector<int>> graph, int number_of_nodes)
      : neighbor_degree_(number_of_nodes, 0) {
    graph_ = graph;
    number_of_nodes_ = number_of_nodes;
  }
  void AddEdge(int in_vertex, int out_vertex) {
    graph_[in_vertex].push_back(out_vertex);
    neighbor_degree_[out_vertex]++;
  }
  std::vector<int> TopologicalSort() {
    std::vector<int> temp_neighbors = neighbor_degree_;
    std::stack<int> traversing_stack;
    for (int i = 0; i < number_of_nodes_; i++) {
      if (temp_neighbors[i] == 0) {
        traversing_stack.push(i);
      }
    }
    std::vector<int> topological_order;
    while (!traversing_stack.empty()) {
      int current_node = traversing_stack.top();
      traversing_stack.pop();
      topological_order.push_back(current_node);
      for (int i : graph_[current_node]) {
        if (--temp_neighbors[i] == 0) {
          traversing_stack.push(i);
        }
      }
    }
    unsigned long number_of_nodes = number_of_nodes_;
    return (topological_order.size() == number_of_nodes) ? topological_order : std::vector<int>();
  }
};
int main() {
  int number_of_nodes, number_of_edges;
  int in_vertex, out_vertex;
  if (scanf("%d %d", &number_of_nodes, &number_of_edges) != 2) {
    fprintf(stderr, "Expected two values as input");
  }
  std::vector<std::vector<int>> adjacency_matrix(number_of_nodes);
  Graph graph(adjacency_matrix, number_of_nodes);
  for (int i = 0; i < number_of_edges; i++) {
    if (scanf("%d %d", &in_vertex, &out_vertex) != 2) {
      fprintf(stderr, "Expected two values as input");
    }
    graph.AddEdge(in_vertex, out_vertex);
  }
  std::vector<int> order = graph.TopologicalSort();
  if (order.empty()) {
    printf("NO");
  } else {
    printf("YES\n");
    for (std::size_t i = 0; i < order.size(); i++) {
      if (i == order.size() - 1) {
        printf("%d", order[i]);
        break;
      }
      printf("%d ", order[i]);
    }
  }
  return 0;
}
