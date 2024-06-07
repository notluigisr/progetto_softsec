  bool is_capacity_full() const TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return has_capacity() && map_.size() >= capacity_;
  }