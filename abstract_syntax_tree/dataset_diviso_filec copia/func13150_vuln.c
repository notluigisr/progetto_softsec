  void readStructEnd() {
    lastFieldId_ = nestedStructFieldIds_.back();
    nestedStructFieldIds_.pop_back();
  }