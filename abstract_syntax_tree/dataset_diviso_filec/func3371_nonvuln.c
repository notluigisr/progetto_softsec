void ConnectionImpl::completeLastHeader() {
  ENVOY_CONN_LOG(trace, "STR", connection_,
                 current_header_field_.getStringView(), current_header_value_.getStringView());

  checkHeaderNameForUnderscores();
  auto& headers_or_trailers = headersOrTrailers();
  if (!current_header_field_.empty()) {
    current_header_field_.inlineTransform([](char c) { return absl::ascii_tolower(c); });
    
    
    
    current_header_value_.rtrim();
    headers_or_trailers.addViaMove(std::move(current_header_field_),
                                   std::move(current_header_value_));
  }

  
  if (headers_or_trailers.size() > max_headers_count_) {
    error_code_ = Http::Code::RequestHeaderFieldsTooLarge;
    sendProtocolError(Http1ResponseCodeDetails::get().TooManyHeaders);
    const absl::string_view header_type =
        processing_trailers_ ? Http1HeaderTypes::get().Trailers : Http1HeaderTypes::get().Headers;
    throw CodecProtocolException(absl::StrCat(header_type, "STR"));
  }

  header_parsing_state_ = HeaderParsingState::Field;
  ASSERT(current_header_field_.empty());
  ASSERT(current_header_value_.empty());
}