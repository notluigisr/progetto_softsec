bool Filter::maybeRetryReset(Http::StreamResetReason reset_reason,
                             UpstreamRequest& upstream_request) {
  
  
  
  if (downstream_response_started_ || !retry_state_ || upstream_request.retried()) {
    return false;
  }

  const RetryStatus retry_status =
      retry_state_->shouldRetryReset(reset_reason, [this]() -> void { doRetry(); });
  if (retry_status == RetryStatus::Yes) {
    runRetryOptionsPredicates(upstream_request);
    pending_retries_++;

    if (upstream_request.upstreamHost()) {
      upstream_request.upstreamHost()->stats().rq_error_.inc();
    }

    auto request_ptr = upstream_request.removeFromList(upstream_requests_);
    if (Runtime::runtimeFeatureEnabled("STR")) {
      request_ptr->cleanUp();
      callbacks_->dispatcher().deferredDelete(std::move(request_ptr));
    }
    return true;
  } else if (retry_status == RetryStatus::NoOverflow) {
    callbacks_->streamInfo().setResponseFlag(StreamInfo::ResponseFlag::UpstreamOverflow);
  } else if (retry_status == RetryStatus::NoRetryLimitExceeded) {
    callbacks_->streamInfo().setResponseFlag(StreamInfo::ResponseFlag::UpstreamRetryLimitExceeded);
  }

  return false;
}