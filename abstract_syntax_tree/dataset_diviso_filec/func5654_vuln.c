  void RemoveZeroOperations() {
    RemoveZeroAdd(&added_lower_index_, &added_lower_offset_);
    RemoveZeroAdd(&added_upper_index_, &added_upper_offset_);
  }