    CImg<T> get_unroll(const char axis) const {
      return (+*this).unroll(axis);
    }