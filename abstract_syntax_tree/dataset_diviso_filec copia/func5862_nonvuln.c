bool IsPowerOfTwo(uint32_t v) { return v && !(v & (v - 1)); }