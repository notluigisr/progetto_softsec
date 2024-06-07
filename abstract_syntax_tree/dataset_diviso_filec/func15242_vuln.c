void ConnectionImpl::onHeaderValue(const char* data, size_t length) {
  if (header_parsing_state_ == HeaderParsingState::Done) {
    
    return;
  }

  const absl::string_view header_value = absl::string_view(data, length);

  if (strict_header_validation_) {
    if (!Http::HeaderUtility::headerIsValid(header_value)) {
      ENVOY_CONN_LOG(debug, "STR", connection_, header_value);
      error_code_ = Http::Code::BadRequest;
      sendProtocolError();
      throw CodecProtocolException("STR");
    }
  } else if (header_value.find('\0') != absl::string_view::npos) {
    
    
    
    
    throw CodecProtocolException("STR");
  }

  header_parsing_state_ = HeaderParsingState::Value;
  current_header_value_.append(data, length);

  const uint32_t total =
      current_header_field_.size() + current_header_value_.size() + current_header_map_->byteSize();
  if (total > (max_request_headers_kb_ * 1024)) {
    error_code_ = Http::Code::RequestHeaderFieldsTooLarge;
    sendProtocolError();
    throw CodecProtocolException("STR");
  }
}