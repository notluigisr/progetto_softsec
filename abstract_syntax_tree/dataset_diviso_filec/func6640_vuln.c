    inline void skip(int bytes) {
      while (bytes > 0) {
        int n = check(1, bytes);
        ptr += n;
        bytes -= n;
      }
    }