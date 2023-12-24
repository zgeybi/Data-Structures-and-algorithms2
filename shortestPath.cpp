//
// Created by tim on 07.11.23.
//
#include <algorithm>
#include <climits>
#include <cstdio>
#include <queue>
#include <vector>

void BFS(std::vector<std::vector<int> >& graph, int number_of_nodes, int start,
         std::vector<int>& dist) {
  std::queue<int> queue;
  std::vector<bool> visited(number_of_nodes + 1, false);
  visited[start] = true;
  dist[start] = 0;
  queue.push(start);
  while (!queue.empty()) {
    int current_node = queue.front();
    queue.pop();
    for (long unsigned int i = 0; i < graph[current_node].size(); i++) {
      if (!visited[graph[current_node][i]]) {
        visited[graph[current_node][i]] = true;
        dist[graph[current_node][i]] = dist[current_node] + 1;
        queue.push(graph[current_node][i]);
      }
    }
  }
}
int ShortestPath(std::vector<std::vector<int> >& graph, int number_of_nodes,
                 int first_target, int second_target, int store) {
  std::vector<int> first_target_dist(number_of_nodes + 1, INT_MAX);
  std::vector<int> second_target_dist(number_of_nodes + 1, INT_MAX);
  std::vector<int> store_dist(number_of_nodes + 1, INT_MAX);
  BFS(graph, number_of_nodes, first_target, first_target_dist);
  BFS(graph, number_of_nodes, second_target, second_target_dist);
  BFS(graph, number_of_nodes, store, store_dist);
  int edges = 2 * number_of_nodes;
  for (int i = 1; i <= number_of_nodes; i++) {
    int distance = first_target_dist[i] + second_target_dist[i] + store_dist[i];
    if (distance < edges) {
      edges = distance;
    }
  }
  return edges;
}
int main() {
  int number_of_nodes, number_of_edges, leon, matilda, store, in_edge, out_edge;
  if (scanf("%d %d %d %d %d", &number_of_nodes, &number_of_edges, &leon,
            &matilda, &store) != 5) {
    fprintf(stderr, "Expected 5 values as input\n");
    exit(1);
  }
  std::vector<std::vector<int> > graph(number_of_nodes + 1);
  for (int i = 0; i < number_of_edges; i++) {
    if (scanf("%d %d", &in_edge, &out_edge) != 2) {
      fprintf(stderr, "Expected 2 numbers as input");
      exit(1);
    }
    graph[in_edge].push_back(out_edge);
    graph[out_edge].push_back(in_edge);
  }

  printf("%d", ShortestPath(graph, number_of_nodes, matilda, leon, store));
  return 0;
}