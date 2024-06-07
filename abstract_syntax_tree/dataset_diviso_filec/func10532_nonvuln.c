void ConnectionImpl::addIntToBuffer(uint64_t i) {
  reserved_current_ += StringUtil::itoa(reserved_current_, bufferRemainingSize(), i);
}