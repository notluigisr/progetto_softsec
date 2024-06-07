HttpIntegrationTest::waitForNextUpstreamRequest(const std::vector<uint64_t>& upstream_indices) {
  uint64_t upstream_with_request;
  
  if (!fake_upstream_connection_) {

    AssertionResult result = AssertionFailure();
    for (auto upstream_index : upstream_indices) {
      result = fake_upstreams_[upstream_index]->waitForHttpConnection(
          *dispatcher_, fake_upstream_connection_, TestUtility::DefaultTimeout,
          max_request_headers_kb_);
      if (result) {
        upstream_with_request = upstream_index;
        break;
      }
    }
    RELEASE_ASSERT(result, result.message());
  }
  
  AssertionResult result =
      fake_upstream_connection_->waitForNewStream(*dispatcher_, upstream_request_);
  RELEASE_ASSERT(result, result.message());
  
  result = upstream_request_->waitForEndStream(*dispatcher_);
  RELEASE_ASSERT(result, result.message());

  return upstream_with_request;
}