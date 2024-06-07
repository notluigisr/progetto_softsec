  void growRing() {
    if (size_ < capacity_) {
      return;
    }
    const size_t new_capacity = capacity_ * 2;
    auto new_ring = std::make_unique<SlicePtr[]>(new_capacity);
    for (size_t i = 0; i < new_capacity; i++) {
      ASSERT(new_ring[i] == nullptr);
    }
    size_t src = start_;
    size_t dst = 0;
    for (size_t i = 0; i < size_; i++) {
      new_ring[dst++] = std::move(ring_[src++]);
      if (src == capacity_) {
        src = 0;
      }
    }
    for (size_t i = 0; i < capacity_; i++) {
      ASSERT(ring_[i].get() == nullptr);
    }
    external_ring_.swap(new_ring);
    ring_ = external_ring_.get();
    start_ = 0;
    capacity_ = new_capacity;
  }