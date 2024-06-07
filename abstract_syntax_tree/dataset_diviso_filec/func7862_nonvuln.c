TEST_P(ProtocolIntegrationTest, 304WithBody) {
  initialize();

  codec_client_ = makeHttpConnection(lookupPort("STR"));

  auto response = codec_client_->makeHeaderOnlyRequest(default_request_headers_);

  waitForNextUpstreamRequest();
  Http::TestResponseHeaderMapImpl response_headers{{"STR"}};
  ASSERT(upstream_request_ != nullptr);
  upstream_request_->encodeHeaders(response_headers, false);
  response->waitForHeaders();
  EXPECT_EQ("STR", response->headers().getStatusValue());

  
  
  if (downstream_protocol_ == Http::CodecType::HTTP1 ||
      upstreamProtocol() == Http::CodecType::HTTP1) {
    ASSERT_TRUE(response->complete());
  } else {
    ASSERT_FALSE(response->complete());
  }

  upstream_request_->encodeData(2, true);
  if (upstreamProtocol() == Http::CodecType::HTTP1) {
    
    
    
    
    
    
    test_server_->waitForCounterGe("STR", 1);
  }

  
  
  
  if (downstream_protocol_ >= Http::CodecType::HTTP2 &&
      upstreamProtocol() >= Http::CodecType::HTTP2) {
    ASSERT_TRUE(response->waitForReset());
  }
}