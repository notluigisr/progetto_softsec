void Filter::onResponseTimeout() {
  ENVOY_STREAM_LOG(debug, "STR", *callbacks_);

  
  
  if (final_upstream_request_) {
    callbacks_->streamInfo().setUpstreamTiming(final_upstream_request_->upstream_timing_);
  }

  
  while (!upstream_requests_.empty()) {
    UpstreamRequestPtr upstream_request =
        upstream_requests_.back()->removeFromList(upstream_requests_);

    
    
    if (upstream_request->awaiting_headers_) {
      cluster_->stats().upstream_rq_timeout_.inc();
      if (upstream_request->upstream_host_) {
        upstream_request->upstream_host_->stats().rq_timeout_.inc();
      }

      
      
      if (!upstream_request->outlier_detection_timeout_recorded_) {
        updateOutlierDetection(Upstream::Outlier::Result::LOCAL_ORIGIN_TIMEOUT, *upstream_request,
                               absl::optional<uint64_t>(enumToInt(timeout_response_code_)));
      }

      chargeUpstreamAbort(timeout_response_code_, false, *upstream_request);
    }
    upstream_request->resetStream();
  }

  onUpstreamTimeoutAbort(StreamInfo::ResponseFlag::UpstreamRequestTimeout,
                         StreamInfo::ResponseCodeDetails::get().UpstreamTimeout);
}