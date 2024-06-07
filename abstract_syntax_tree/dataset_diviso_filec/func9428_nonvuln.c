void ConnectionImpl::StreamImpl::encodeTrailers(const HeaderMap& trailers) {
  ASSERT(!local_end_stream_);
  local_end_stream_ = true;
  if (pending_send_data_.length() > 0) {
    
    
    ASSERT(!pending_trailers_);
    pending_trailers_ = std::make_unique<HeaderMapImpl>(trailers);
  } else {
    submitTrailers(trailers);
    parent_.sendPendingFrames();
  }
}