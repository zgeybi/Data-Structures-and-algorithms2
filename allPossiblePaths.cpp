//
// Created by tim on 21.11.23.
//

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

template <typename T>
std::vector<std::vector<T>> MultiplyMatrices(
    std::vector<std::vector<T>> first_matrix,
    std::vector<std::vector<T>> second_matrix) {
  std::size_t size = first_matrix.size();
  std::vector<std::vector<T>> result(size, std::vector<T>(size, 0));
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      for (std::size_t k = 0; k < size; k++) {
        if ((first_matrix[i][k] & second_matrix[k][j]) == 1) {
          result[i][j] = first_matrix[i][k] & second_matrix[k][j];
          break;
        }
      }
    }
  }
  return result;
}
template <typename T>
std::vector<std::vector<T>> AddMatrices(
    std::vector<std::vector<T>> first_matrix,
    std::vector<std::vector<T>> second_matrix) {
  std::size_t size = first_matrix.size();
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      first_matrix[i][j] |= first_matrix[i][j] | second_matrix[i][j];
    }
  }
  return first_matrix;
}
template <typename T>
std::pair<std::vector<std::vector<T>>, std::vector<std::vector<T>>> PowerMatrix(
    std::vector<std::vector<T>> matrix, T number_of_nodes) {
  if (number_of_nodes == 0) {
    return std::make_pair(matrix,
                          std::vector<std::vector<T>>(1, std::vector<T>(1, 0)));
  }
  if (number_of_nodes == 1) {
    return std::make_pair(matrix, matrix);
  }
  if (number_of_nodes == 2) {
    std::vector<std::vector<T>> multiplied_matrix =
        MultiplyMatrices<T>(matrix, matrix);
    return std::make_pair(multiplied_matrix,
                          AddMatrices(matrix, multiplied_matrix));
  }
  if (number_of_nodes % 2 == 0) {
    auto result = PowerMatrix<T>(matrix, number_of_nodes / 2);
    auto multiplied_sum = MultiplyMatrices<T>(result.first, result.second);
    return std::make_pair(MultiplyMatrices<T>(result.first, result.first),
                          AddMatrices<T>(result.second, multiplied_sum));
  }
  auto result = PowerMatrix<T>(matrix, (number_of_nodes - 1) / 2);
  return std::make_pair(
      MultiplyMatrices<T>(result.first, matrix),
      AddMatrices<T>(result.second, MultiplyMatrices(result.first, matrix)));
}

int main() {
  int number_of_nodes;
  char place_holder;
  std::cin >> number_of_nodes;
  std::vector<std::vector<short>> adjacency_matrix(
      number_of_nodes, std::vector<short>(number_of_nodes, 0));
  for (int i = 0; i < number_of_nodes; i++) {
    for (int j = 0; j < number_of_nodes; j++) {
      std::cin >> place_holder;
      if (place_holder == '1') {
        adjacency_matrix[i][j] = 1;
      }
    }
  }
  auto result = PowerMatrix<short>(adjacency_matrix, number_of_nodes - 1);

  for (auto i : result.second) {
    for (auto j : i) {
      std::cout << j;
    }
    std::cout << '\n';
  }
  return 0;
}
