  void doMetadata() override {
    if (saved_request_metadata_ != nullptr) {
      drainSavedRequestMetadata();
    }
  }