static BROTLI_INLINE void SortHuffmanTreeItems(HuffmanTree* items,
    const size_t n, HuffmanTreeComparator comparator) {
  static const size_t gaps[] = {132, 57, 23, 10, 4, 1};
  if (n < 13) {
    
    size_t i;
    for (i = 1; i < n; ++i) {
      HuffmanTree tmp = items[i];
      size_t k = i;
      size_t j = i - 1;
      while (comparator(&tmp, &items[j])) {
        items[k] = items[j];
        k = j;
        if (!j--) break;
      }
      items[k] = tmp;
    }
    return;
  } else {
    
    int g = n < 57 ? 2 : 0;
    for (; g < 6; ++g) {
      size_t gap = gaps[g];
      size_t i;
      for (i = gap; i < n; ++i) {
        size_t j = i;
        HuffmanTree tmp = items[i];
        for (; j >= gap && comparator(&tmp, &items[j - gap]); j -= gap) {
          items[j] = items[j - gap];
        }
        items[j] = tmp;
      }
    }
  }
}