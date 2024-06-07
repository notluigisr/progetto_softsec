    void convert(const char * in0, int size, CharVector & out) const {
      if (size == -1) {
        const Chr * in = reinterpret_cast<const Chr *>(in0);
        for (;*in != 0; ++in)
          out.append(in, sizeof(Chr));
      } else {
        out.append(in0, size);
      }
    }