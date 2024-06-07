IntegrationStreamDecoderPtr HttpIntegrationTest::sendRequestAndWaitForResponse(
    const Http::TestHeaderMapImpl& request_headers, uint32_t request_body_size,
    const Http::TestHeaderMapImpl& response_headers, uint32_t response_size, int upstream_index) {
  ASSERT(codec_client_ != nullptr);
  
  IntegrationStreamDecoderPtr response;
  if (request_body_size) {
    response = codec_client_->makeRequestWithBody(request_headers, request_body_size);
  } else {
    response = codec_client_->makeHeaderOnlyRequest(request_headers);
  }
  waitForNextUpstreamRequest(upstream_index);
  
  upstream_request_->encodeHeaders(response_headers, response_size == 0);
  
  if (response_size) {
    upstream_request_->encodeData(response_size, true);
  }
  
  response->waitForEndStream();
  return response;
}