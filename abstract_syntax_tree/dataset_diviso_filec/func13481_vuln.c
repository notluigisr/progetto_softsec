void ConnectionImpl::onHeaderValue(const char* data, size_t length) {
  if (header_parsing_state_ == HeaderParsingState::Done && !enable_trailers_) {
    
    return;
  }

  if (processing_trailers_) {
    maybeAllocTrailers();
  }

  absl::string_view header_value{data, length};

  if (strict_header_validation_) {
    if (!Http::HeaderUtility::headerValueIsValid(header_value)) {
      ENVOY_CONN_LOG(debug, "STR", connection_, header_value);
      error_code_ = Http::Code::BadRequest;
      sendProtocolError(Http1ResponseCodeDetails::get().InvalidCharacters);
      throw CodecProtocolException("STR");
    }
  }

  header_parsing_state_ = HeaderParsingState::Value;
  if (current_header_value_.empty()) {
    
    
    
    
    header_value = StringUtil::ltrim(header_value);
  }
  current_header_value_.append(header_value.data(), header_value.length());

  const uint32_t total =
      current_header_field_.size() + current_header_value_.size() + headersOrTrailers().byteSize();
  if (total > (max_headers_kb_ * 1024)) {
    const absl::string_view header_type =
        processing_trailers_ ? Http1HeaderTypes::get().Trailers : Http1HeaderTypes::get().Headers;
    error_code_ = Http::Code::RequestHeaderFieldsTooLarge;
    sendProtocolError(Http1ResponseCodeDetails::get().HeadersTooLarge);
    throw CodecProtocolException(absl::StrCat(header_type, "STR"));
  }
}