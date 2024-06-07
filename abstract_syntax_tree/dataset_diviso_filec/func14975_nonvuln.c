
    
    
    T& max() {
      bool is_all_empty = true;
      T *ptr_max = 0;
      cimglist_for(*this,l) if (!_data[l].is_empty()) {
        ptr_max = _data[l]._data;
        is_all_empty = false;
        break;
      }
      if (is_all_empty)
        throw CImgInstanceException(_cimglist_instance
                                    "STR",
                                    _data?"STR",
                                    cimglist_instance);
      T max_value = *ptr_max;
      cimglist_for(*this,l) {
        const CImg<T>& img = _data[l];