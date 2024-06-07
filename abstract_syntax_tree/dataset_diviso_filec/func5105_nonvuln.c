StatusOr<ParserStatus> ConnectionImpl::onMessageComplete() {
  ENVOY_CONN_LOG(trace, "STR", connection_);

  dispatchBufferedBody();

  if (handling_upgrade_) {
    
    
    ASSERT(!deferred_end_stream_headers_);
    ENVOY_CONN_LOG(trace, "STR", connection_);
    return parser_->pause();
  }

  
  
  if (header_parsing_state_ == HeaderParsingState::Value) {
    RETURN_IF_ERROR(completeLastHeader());
  }

  return onMessageCompleteBase();
}