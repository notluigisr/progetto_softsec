void ServerConnectionImpl::onResetStream(StreamResetReason reason) {
  ASSERT(active_request_);
  active_request_->response_encoder_.runResetCallbacks(reason);
  active_request_.reset();
}