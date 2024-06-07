      TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return has_memory_limit() && bytes + current_bytes_ > memory_limit_;
  }