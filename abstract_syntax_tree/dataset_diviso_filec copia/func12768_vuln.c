  void Update(const char* str, size_t size) {
    if (str_ == NULL)
      str_ = str;
    else if (on_heap_ || str_ + size != str) {
      
      
      char* s = new char[size_ + size];
      memcpy(s, str_, size_);
      memcpy(s + size_, str, size);

      if (on_heap_)
        delete[] str_;
      else
        on_heap_ = true;

      str_ = s;
    }
    size_ += size;
  }