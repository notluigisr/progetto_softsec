    inline int check(int itemSize, int nItems=1)
    {
      if (ptr + itemSize * nItems > end) {
        if (ptr + itemSize > end)
          return overrun(itemSize, nItems);

        nItems = (end - ptr) / itemSize;
      }
      return nItems;
    }