  void notify_inserters_if_bounded() TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    if (has_capacity() || has_memory_limit()) {
      
      
      
      full_.notify_all();
    }
  }