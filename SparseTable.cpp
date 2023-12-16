//
// Created by Tim on 12/12/2023.
//

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
unsigned int LogBaseTwo(unsigned int value) {
  if (value == 0) {
    return -1;
  }
  unsigned int result = 0;
  while (value >>= 1) {
    ++result;
  }
  return result;
}
template <typename T>
class SparseTable {
 private:
  std::vector<std::vector<std::pair<T, T>>> table_;
 public:
  void PrecomputeTable(std::vector<T>& sequence) {
    T number_of_terms = sequence.size();
    T depth = static_cast<T>(LogBaseTwo(number_of_terms) + 1);
    table_.resize(number_of_terms, std::vector<std::pair<T, T>>(depth, {0, 0}));
    for (int i = 0; i < number_of_terms; ++i) {
      table_[i][0] = {sequence[i], i};
    }
    for (int j = 1; (1 << j) <= number_of_terms; ++j) {
      for (int i = 0; i + (1 << j) - 1 < number_of_terms; ++i) {
        std::pair<T, T> left = table_[i][j - 1];
        std::pair<T, T> right = table_[i + (1 << (j - 1))][j - 1];
        table_[i][j] = std::min(left, right);
      }
    }
  }
  std::pair<T, T> ProcessQuery(int left, int right) {
    T j = static_cast<T>(LogBaseTwo(right - left + 1));
    std::pair<T, T> left_part = table_[left][j];
    std::pair<T, T> right_part = table_[right - (1 << j) + 1][j];
    return std::min(left_part, right_part);
  }
};
template <typename T>
T SecondOrder(SparseTable<T>& sparse_table, const std::vector<T>& sequence,
              int left, int right) {
  std::pair<T, T> min = sparse_table.ProcessQuery(left - 1, right - 1);
  T min_index = min.second;
  T second_order = std::numeric_limits<T>::max();
  if (left - 1 <= min_index - 1) {
    second_order = std::min(
        second_order,
        sequence[sparse_table.ProcessQuery(left - 1, min_index - 1).second]);
  }
  if (min_index + 1 <= right - 1) {
    second_order = std::min(
        second_order,
        sequence[sparse_table.ProcessQuery(min_index + 1, right - 1).second]);
  }
  return second_order;
}

int main() {
  SparseTable<int> sparse_table;
  int number_of_terms, M;
  std::cin >> number_of_terms >> M;
  std::vector<int> sequence(number_of_terms);
  for (int i = 0; i < number_of_terms; i++) {
    std::cin >> sequence[i];
  }
  sparse_table.PrecomputeTable(sequence);
  for (int i = 0; i < M; i++) {
    int left, right;
    std::cin >> left >> right;
    int min2 = SecondOrder<int>(sparse_table, sequence, left, right);
    std::cout << min2 << '\n';
  }
  return 0;
}