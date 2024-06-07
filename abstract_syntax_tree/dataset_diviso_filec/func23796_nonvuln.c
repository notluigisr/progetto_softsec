void Filter::doRetry() {
  ENVOY_STREAM_LOG(debug, "STR", *callbacks_);

  is_retry_ = true;
  attempt_count_++;
  ASSERT(pending_retries_ > 0);
  pending_retries_--;

  
  const auto cluster = config_.cm_.getThreadLocalCluster(route_entry_->clusterName());
  std::unique_ptr<GenericConnPool> generic_conn_pool;
  if (cluster != nullptr) {
    cluster_ = cluster->info();
    generic_conn_pool = createConnPool(*cluster);
  }

  if (!generic_conn_pool) {
    sendNoHealthyUpstreamResponse();
    cleanup();
    return;
  }
  UpstreamRequestPtr upstream_request =
      std::make_unique<UpstreamRequest>(*this, std::move(generic_conn_pool));

  if (include_attempt_count_in_request_) {
    downstream_headers_->setEnvoyAttemptCount(attempt_count_);
  }

  UpstreamRequest* upstream_request_tmp = upstream_request.get();
  LinkedList::moveIntoList(std::move(upstream_request), upstream_requests_);
  upstream_requests_.front()->encodeHeaders(!callbacks_->decodingBuffer() &&
                                            !downstream_trailers_ && downstream_end_stream_);
  
  
  
  if (!upstream_requests_.empty() && (upstream_requests_.front().get() == upstream_request_tmp)) {
    if (callbacks_->decodingBuffer()) {
      
      Buffer::OwnedImpl copy(*callbacks_->decodingBuffer());
      upstream_requests_.front()->encodeData(copy, !downstream_trailers_ && downstream_end_stream_);
    }

    if (downstream_trailers_) {
      upstream_requests_.front()->encodeTrailers(*downstream_trailers_);
    }
  }
}