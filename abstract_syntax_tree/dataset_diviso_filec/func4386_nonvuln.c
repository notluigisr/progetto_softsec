    
    CImg<T> get_dilate(const unsigned int s) const {
      return (+*this).dilate(s);