    CImg<T> get_min(const T& value) const {
      return (+*this).min(value);
    }