  void addDrainTracker(std::function<void()> drain_tracker) {
    drain_trackers_.emplace_back(std::move(drain_tracker));
  }