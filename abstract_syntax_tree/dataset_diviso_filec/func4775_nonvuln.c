bool ConnectionManagerImpl::ActiveStreamDecoderFilter::recreateStream() {
  
  
  
  if (!complete() || parent_.stream_info_.bytesReceived() != 0) {
    return false;
  }
  
  
  
  HeaderMapPtr request_headers(std::move(parent_.request_headers_));
  StreamEncoder* response_encoder = parent_.response_encoder_;
  parent_.response_encoder_ = nullptr;
  
  
  parent_.connection_manager_.doEndStream(this->parent_);

  StreamDecoder& new_stream = parent_.connection_manager_.newStream(*response_encoder, true);
  new_stream.decodeHeaders(std::move(request_headers), true);
  return true;
}