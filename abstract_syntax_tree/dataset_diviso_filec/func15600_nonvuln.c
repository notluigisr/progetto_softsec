    
    const CImg<T>& save_ascii(std::FILE *const file) const {
      return _save_ascii(file,0);