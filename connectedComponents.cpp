//
// Created by Tim on 12/24/2023.
//

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

template <typename T>
int FindIndex(const std::vector<std::vector<T>>& components, T vertex) {
  for (size_t i = 0; i < components.size(); ++i) {
    if (std::find(components[i].begin(), components[i].end(), vertex) !=
        components[i].end()) {
      return static_cast<int>(i);
    }
  }
  return -1;
}

template <typename T>
struct Graph {
  std::vector<std::vector<T>> adjacency;
  std::vector<std::vector<T>> reversed_adjacency;
  Graph(int number_of_nodes) {
    adjacency = std::vector<std::vector<int>>(number_of_nodes);
    reversed_adjacency = std::vector<std::vector<int>>(number_of_nodes);
  }
  void AddEdge(T in_vertex, T out_vertex) {
    adjacency[in_vertex].push_back(out_vertex);
    reversed_adjacency[out_vertex].push_back(in_vertex);
  }
  Graph<T> Squeeze(const std::vector<std::vector<T>>& components) {
    int size = components.size();
    Graph<T> xo(size);
    for (const auto& component : components) {
      for (auto vertex : component) {
        for (auto neighbor : adjacency[vertex]) {
          T component_index = FindIndex(components, vertex);
          T neighbor_index = FindIndex(components, neighbor);
          if (component_index != neighbor_index) {
            xo.AddEdge(component_index, neighbor_index);
          }
        }
      }
    }
    return xo;
  }
};

template <typename T>
std::pair<T, T> FindDegree(std::vector<std::vector<T>>& adjacency,
                           T number_of_nodes) {
  std::vector<T> din(number_of_nodes, 0);
  std::vector<T> dout(number_of_nodes, 0);

  for (int i = 0; i < number_of_nodes; ++i) {
    for (T neighbor : adjacency[i]) {
      dout[i]++;
      din[neighbor]++;
    }
  }

  int total_degrees_in = std::count(din.begin(), din.end(), 0);
  int total_degrees_out = std::count(dout.begin(), dout.end(), 0);

  return {total_degrees_in, total_degrees_out};
}
template <typename T>
void DFS(std::vector<std::vector<T>>& adjacency, T vertex,
         std::vector<bool>& visited, std::stack<T>& traversal_stack) {
  visited[vertex] = true;
  for (T neighbor : adjacency[vertex]) {
    if (!visited[neighbor]) {
      DFS(adjacency, neighbor, visited, traversal_stack);
    }
  }
  traversal_stack.push(vertex);
}
template <typename T>
void Change(std::vector<std::vector<T>>& reversed_adjacency, T vertex,
            std::vector<bool>& visited, std::vector<T>& component) {
  visited[vertex] = true;
  component.emplace_back(vertex);
  for (auto neighbor : reversed_adjacency[vertex]) {
    if (!visited[neighbor]) {
      Change(reversed_adjacency, neighbor, visited, component);
    }
  }
}
template <typename T>
std::vector<std::vector<T>> Process(
    std::vector<std::vector<T>>& adjacency,
    std::vector<std::vector<T>>& reversed_adjacency, T number_of_nodes) {
  std::stack<T> traversal_stack;
  std::vector<bool> visited(number_of_nodes, false);

  for (int i = 0; i < number_of_nodes; ++i) {
    if (!visited[i]) {
      DFS<T>(adjacency, i, visited, traversal_stack);
    }
  }
  visited.assign(number_of_nodes, false);
  std::vector<std::vector<T>> strongly_connected_component;
  while (!traversal_stack.empty()) {
    T list = traversal_stack.top();
    traversal_stack.pop();
    if (!visited[list]) {
      std::vector<T> connected_component;
      Change(reversed_adjacency, list, visited, connected_component);
      strongly_connected_component.emplace_back(connected_component);
    }
  }
  return strongly_connected_component;
}

int main() {
  int number_of_nodes, number_of_edges;
  std::cin >> number_of_nodes >> number_of_edges;
  Graph<int> graph(number_of_nodes);
  int in_vertex, out_vertex, count = 0;
  while (count < number_of_edges) {
    std::cin >> in_vertex >> out_vertex;
    graph.AddEdge(in_vertex - 1, out_vertex - 1);
    count++;
  }
  std::vector<std::vector<int>> map =
      Process<int>(graph.adjacency, graph.reversed_adjacency, number_of_nodes);
  if (map.size() == 1) {
    std::cout << 0 << '\n';
    return 0;
  }
  if (map.empty()) {
    std::cout << 0 << '\n';
    return 0;
  }
  Graph<int> ovo = graph.Squeeze(map);
  std::pair<int, int> res = FindDegree<int>(ovo.adjacency, number_of_nodes);
  std::cout << std::max(res.first, res.second) << '\n';
  return 0;
}
