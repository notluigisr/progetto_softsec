    CImg<T>& load_png(const char *const filename, unsigned int *const bits_per_value=0) {
      return _load_png(0,filename,bits_per_value);
    }