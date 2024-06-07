    inline void pad(int bytes) {
      while (bytes-- > 0) writeU8(0);
    }