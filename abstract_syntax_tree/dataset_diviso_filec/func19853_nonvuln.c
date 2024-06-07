  explicit BlockingWriteServer(AsyncSSLSocket::UniquePtr socket)
      : socket_(std::move(socket)), bufSize_(2500 * 2000), bytesRead_(0) {
    buf_ = std::make_unique<uint8_t[]>(bufSize_);
    socket_->sslAccept(this, std::chrono::milliseconds(100));
  }