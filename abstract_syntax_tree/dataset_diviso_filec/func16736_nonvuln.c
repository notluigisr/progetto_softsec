  void writeSuccess() noexcept override {
    if (socket_) {
      socket_->close();
    }
  }