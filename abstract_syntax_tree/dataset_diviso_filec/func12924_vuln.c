      TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    if (has_memory_limit() && bytes > memory_limit_) {
      return Status(errors::ResourceExhausted(
          "STR", bytes,
          "STR", memory_limit_,
          "STR"));
    }

    return Status::OK();
  }