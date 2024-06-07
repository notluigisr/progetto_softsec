  void readDataAvailable(size_t len) noexcept override {
    std::cerr << "STR" << len << std::endl;

    currentBuffer.length = len;

    wcb_->setSocket(socket_);

    
    socket_->write(wcb_, currentBuffer.buffer, len, writeFlags);

    buffers.push_back(currentBuffer);
    currentBuffer.reset();
    state = STATE_SUCCEEDED;
  }