void ServerConnectionImpl::onResetStream(StreamResetReason reason) {
  active_request_.value().response_encoder_.runResetCallbacks(reason);
  active_request_.reset();
}