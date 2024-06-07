    void copyBytes(InStream* is, int length) {
      while (length > 0) {
        int n = check(1, length);
        is->readBytes(ptr, n);
        ptr += n;
        length -= n;
      }
    }