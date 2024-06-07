    int overrun(int itemSize, int nItems) {
      int len = ptr - start + itemSize * nItems;
      if (len < (end - start) * 2)
        len = (end - start) * 2;

      U8* newStart = new U8[len];
      memcpy(newStart, start, ptr - start);
      ptr = newStart + (ptr - start);
      delete [] start;
      start = newStart;
      end = newStart + len;

      return nItems;
    }