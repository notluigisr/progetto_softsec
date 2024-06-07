    
    template<typename t>
    const T& min_max(t& max_val) const {
      if (is_empty())
        throw CImgInstanceException(_cimglist_instance
                                    "STR",
                                    cimglist_instance);
      const T *ptr_min = _data->_data;
      T min_value = *ptr_min, max_value = min_value;
      cimglist_for(*this,l) {
        const CImg<T>& img = _data[l];
        cimg_for(img,ptrs,T) {
          const T val = *ptrs;
          if (val<min_value) { min_value = val; ptr_min = ptrs; }
          if (val>max_value) max_value = val;
        }