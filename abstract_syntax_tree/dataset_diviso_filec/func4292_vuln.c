  friend H AbslHashValue(H h, const TensorKey& k) {
    const uint8* d = static_cast<uint8*>(k.data());
    size_t s = k.AllocatedBytes();
    std::vector<uint8> vec;
    vec.reserve(s);
    for (int i = 0; i < s; i++) {
      vec.push_back(d[i]);
    }
    return H::combine(std::move(h), s);
  }