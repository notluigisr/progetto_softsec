void ConnectionManagerImpl::ActiveStream::recreateStream(
    StreamInfo::FilterStateSharedPtr filter_state) {
  
  
  
  ResponseEncoder* response_encoder = response_encoder_;
  response_encoder_ = nullptr;

  Buffer::InstancePtr request_data = std::make_unique<Buffer::OwnedImpl>();
  const auto& buffered_request_data = filter_manager_.bufferedRequestData();
  const bool proxy_body = buffered_request_data != nullptr && buffered_request_data->length() > 0;
  if (proxy_body) {
    request_data->move(*buffered_request_data);
  }

  response_encoder->getStream().removeCallbacks(*this);
  
  
  connection_manager_.doEndStream(*this);

  RequestDecoder& new_stream = connection_manager_.newStream(*response_encoder, true);
  
  
  
  
  
  
  if (filter_state->hasDataAtOrAboveLifeSpan(StreamInfo::FilterState::LifeSpan::Request)) {
    (*connection_manager_.streams_.begin())->filter_manager_.streamInfo().filter_state_ =
        std::make_shared<StreamInfo::FilterStateImpl>(
            filter_state->parent(), StreamInfo::FilterState::LifeSpan::FilterChain);
  }

  new_stream.decodeHeaders(std::move(request_headers_), !proxy_body);
  if (proxy_body) {
    
    
    
    new_stream.decodeData(*request_data, true);
  }
}