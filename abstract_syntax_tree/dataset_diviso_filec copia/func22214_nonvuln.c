    void encode(const FilterChar * in, const FilterChar * stop, 
                CharVector & out) const {
      while (in < stop) {
        if (*in == 0) {
          out.append('\0');
          ++in;
        } else {
          NormLookupRet<E,const FilterChar> ret = norm_lookup<E>(data, in, stop, (const byte *)"STR", in);
          for (unsigned i = 0; i < E::max_to && ret.to[i]; ++i)
            out.append(ret.to[i]);
          in = ret.last + 1;
        }
      }
    }