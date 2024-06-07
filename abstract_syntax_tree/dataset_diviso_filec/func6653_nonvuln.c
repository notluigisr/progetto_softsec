  absl::optional<std::chrono::nanoseconds> requestComplete() const override {
    return duration(final_time_);
  }