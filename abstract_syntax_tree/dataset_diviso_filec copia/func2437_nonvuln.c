    void add(Uni32 chr) {
      Uni32 p = chr & mask;
      data[p]++;
      if (data[p] > max) max = data[p];
    }