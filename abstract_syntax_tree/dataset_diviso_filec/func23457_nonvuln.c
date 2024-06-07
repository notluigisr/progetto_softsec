uint64_t ConnectionImpl::flushOutput(bool end_encode) {
  if (end_encode) {
    
    
    maybeAddSentinelBufferFragment(*output_buffer_);
  }
  const uint64_t bytes_encoded = output_buffer_->length();
  connection().write(*output_buffer_, false);
  ASSERT(0UL == output_buffer_->length());
  return bytes_encoded;
}