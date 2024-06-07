void ConnectionImpl::copyToBuffer(const char* data, uint64_t length) {
  ASSERT(bufferRemainingSize() >= length);
  memcpy(reserved_current_, data, length);
  reserved_current_ += length;
}