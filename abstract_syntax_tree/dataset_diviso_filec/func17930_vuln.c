  bool has_memory_limit() const TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return memory_limit_ > 0;
  }