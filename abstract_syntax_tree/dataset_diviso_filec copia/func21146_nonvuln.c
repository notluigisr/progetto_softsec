  bool String(const char* str, SizeType length, bool copy) {
    if (s.empty()) {
      return false;
    }
    return s.back().do_string(cct, str, length);
  }