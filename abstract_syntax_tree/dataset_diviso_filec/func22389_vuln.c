  uint64_t append(const void* data, uint64_t size) {
    uint64_t copy_size = std::min(size, reservableSize());
    uint8_t* dest = base_ + reservable_;
    reservable_ += copy_size;
    
    memcpy(dest, data, copy_size);
    return copy_size;
  }