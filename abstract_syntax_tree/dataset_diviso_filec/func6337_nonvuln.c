HeaderMap& ConnectionManagerImpl::ActiveStream::addDecodedTrailers() {
  
  ASSERT(state_.filter_call_state_ & FilterCallState::LastDataFrame);

  
  ASSERT(!request_trailers_);

  request_trailers_ = std::make_unique<HeaderMapImpl>();
  return *request_trailers_;
}