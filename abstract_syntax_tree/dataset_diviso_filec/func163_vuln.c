    inline int check(int itemSize, int nItems=1, bool wait=true)
    {
      if (ptr + itemSize * nItems > end) {
        if (ptr + itemSize > end)
          return overrun(itemSize, nItems, wait);

        nItems = (end - ptr) / itemSize;
      }
      return nItems;
    }