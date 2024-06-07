  int getFlagsImpl(
      folly::WriteFlags flags,
      int ) noexcept override {
    return oldCallback_->getFlags(flags, false );
  }