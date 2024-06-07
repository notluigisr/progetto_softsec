void ConnectionImpl::onHeaderField(const char* data, size_t length) {
  
  
  if (header_parsing_state_ == HeaderParsingState::Done) {
    if (!enable_trailers_) {
      
      return;
    }
    processing_trailers_ = true;
    header_parsing_state_ = HeaderParsingState::Field;
  }
  if (header_parsing_state_ == HeaderParsingState::Value) {
    completeLastHeader();
  }

  current_header_field_.append(data, length);
}