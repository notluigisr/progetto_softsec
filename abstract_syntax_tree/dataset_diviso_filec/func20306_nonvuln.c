void LongestPathsLowerBounds(
    int source, const std::pair<int, int>& target_range,
    const std::vector<std::vector<int>>& outputs,
    std::vector<DistanceFromSource>* longest_distance) {
  std::deque<int> queue;
  queue.emplace_front(source);
  while (!queue.empty()) {
    int node = queue.front();
    queue.pop_front();
    for (int fanout : outputs[node]) {
      
      
      
      
      
      if (fanout >= target_range.first && fanout <= target_range.second &&
          (*longest_distance)[fanout] != TWO_OR_GREATER) {
        (*longest_distance)[fanout] =
            (*longest_distance)[fanout] == ZERO ? ONE : TWO_OR_GREATER;
        queue.emplace_front(fanout);
      }
    }
  }
}