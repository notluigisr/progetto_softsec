    
    template<typename t>
    T& min_max(t& max_val) {
      bool is_all_empty = true;
      T *ptr_min = 0;
      cimglist_for(*this,l) if (!_data[l].is_empty()) {
        ptr_min = _data[l]._data;
        is_all_empty = false;
        break;
      }
      if (is_all_empty)
        throw CImgInstanceException(_cimglist_instance
                                    "STR",
                                    _data?"STR",
                                    cimglist_instance);
      T min_value = *ptr_min, max_value = min_value;
      cimglist_for(*this,l) {
        const CImg<T>& img = _data[l];
        cimg_for(img,ptrs,T) {
          const T val = *ptrs;
          if (val<min_value) { min_value = val; ptr_min = ptrs; }
          if (val>max_value) max_value = val;
        }