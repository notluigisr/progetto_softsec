    CImg<T>& maxabs(const T& value) {
      if (is_empty()) return *this;
      const T absvalue = cimg::abs(value);
      cimg_openmp_for(*this,cimg::maxabs(*ptr,value,absvalue),65536);
      return *this;
    }