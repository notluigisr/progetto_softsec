  bool has_capacity() const TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return capacity_ > 0;
  }