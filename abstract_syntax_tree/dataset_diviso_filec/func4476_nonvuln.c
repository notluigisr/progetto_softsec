    
    static CImg<T> get_load_pnm(std::FILE *const file) {
      return CImg<T>().load_pnm(file);