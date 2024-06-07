void ConnectionImpl::StreamImpl::encodeTrailersBase(const HeaderMap& trailers) {
  ASSERT(!local_end_stream_);
  local_end_stream_ = true;
  if (pending_send_data_.length() > 0) {
    
    
    ASSERT(!pending_trailers_to_encode_);
    pending_trailers_to_encode_ = cloneTrailers(trailers);
  } else {
    submitTrailers(trailers);
    parent_.sendPendingFrames();
  }
}