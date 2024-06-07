  void readDataAvailable(size_t len) noexcept override {
    std::cerr << "STR" << len << std::endl;

    currentBuffer.length = len;

    buffers.push_back(currentBuffer);
    currentBuffer.reset();
    state = STATE_SUCCEEDED;

    socket_->setReadCB(nullptr);
    base_->terminateLoopSoon();
  }