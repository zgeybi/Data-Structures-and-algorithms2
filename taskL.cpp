//
// Created by Tim on 12/26/2023.
//
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

template <typename T>
class SegmentTree {
 private:
  std::vector<T> segment_tree_;

 public:
  SegmentTree(int number_of_igloos) {
    segment_tree_ = std::vector<T>(number_of_igloos * 4);
  }
  void BuildTree(std::vector<T> &igloos, int start, int end, int node) {
    if (start == end) {
      segment_tree_[node] = igloos[start];
      return;
    }
    int mid = (start + end) / 2;
    BuildTree(igloos, start, mid, node * 2 + 1);
    BuildTree(igloos, mid + 1, end, node * 2 + 2);
    segment_tree_[node] =
        std::max(segment_tree_[node * 2 + 1], segment_tree_[node * 2 + 2]);
  }
  void UpdateTree(int node, std::pair<int, int> interval,
                  std::pair<int, int> query, T value) {
    if (interval.first > query.second || interval.second < query.first) {
      return;
    }
    if (interval.first == interval.second) {
      segment_tree_[node] += value;
      return;
    }
    int mid = (interval.first + interval.second) / 2;
    UpdateTree(node * 2 + 1, std::make_pair(interval.first, mid), query, value);
    UpdateTree(node * 2 + 2, std::make_pair(mid + 1, interval.second), query,
               value);
    segment_tree_[node] =
        std::max(segment_tree_[2 * node + 1], segment_tree_[2 * node + 2]);
  }
  T GetMax(int start, int end, int node, int left, int right) {
    if (start > right || end < left) {
      return std::numeric_limits<T>::min();
    }
    if (start >= left && end <= right) {
      return segment_tree_[node];
    }
    int mid = (start + end) / 2;
    T left_part = GetMax(start, mid, node * 2 + 1, left, right);
    T right_part = GetMax(mid + 1, end, node * 2 + 2, left, right);
    return std::max(left_part, right_part);
  }
};

int main() {
  int number_of_igloos, number_of_queries, maximum_capacity;
  std::cin >> number_of_igloos;
  SegmentTree<int> segment_tree(number_of_igloos);
  std::vector<int> igloos(number_of_igloos);
  for (int i = 0; i < number_of_igloos; i++) {
    std::cin >> igloos[i];
  }
  std::cin >> maximum_capacity >> number_of_queries;
  segment_tree.BuildTree(igloos, 0, number_of_igloos - 1, 0);
  std::vector<int> failed_attempts;
  for (int i = 0; i < number_of_queries; i++) {
    int temp_start, temp_end, temp_val;
    std::cin >> temp_start >> temp_end >> temp_val;
    if (segment_tree.GetMax(0, number_of_igloos - 1, 0, temp_start,
                            temp_end) +
            temp_val >
        maximum_capacity) {
      failed_attempts.push_back(i);
    } else {
      segment_tree.UpdateTree(0, std::make_pair(0, number_of_igloos - 1),
                              std::make_pair(temp_start, temp_end),
                              temp_val);
    }
  }
  int size = failed_attempts.size();
  for (int i = 0; i < size; i++) {
    std::cout << failed_attempts[i] << ' ';
  }
  return 0;
}
