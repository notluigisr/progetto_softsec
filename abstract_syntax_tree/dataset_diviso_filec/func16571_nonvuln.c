    CImg<T> get_cut(const T& min_value, const T& max_value) const {
      return (+*this).cut(min_value,max_value);
    }