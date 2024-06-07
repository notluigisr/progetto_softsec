    void decode(const char * in0, int size, FilterCharVector & out) const {
      const Chr * in = reinterpret_cast<const Chr *>(in0);
      if (size == -1) {
        for (;*in; ++in)
          out.append(*in);
      } else {
        const Chr * stop = reinterpret_cast<const Chr *>(in0 +size);
        for (;in != stop; ++in)
          out.append(*in);
      }
    }