    void writeBytes(const void* data, int length) {
      check(length);
      memcpy(ptr, data, length);
      ptr += length;
    }