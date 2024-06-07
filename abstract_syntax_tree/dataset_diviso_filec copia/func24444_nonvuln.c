TEST_P(DownstreamProtocolIntegrationTest, BasicMaxStreamTimeout) {
  config_helper_.setDownstreamMaxStreamDuration(std::chrono::milliseconds(500));
  initialize();
  fake_upstreams_[0]->set_allow_unexpected_disconnects(true);
  codec_client_ = makeHttpConnection(lookupPort("STR"));

  auto encoder_decoder = codec_client_->startRequest(default_request_headers_);
  request_encoder_ = &encoder_decoder.first;
  auto response = std::move(encoder_decoder.second);

  ASSERT_TRUE(fake_upstreams_[0]->waitForHttpConnection(*dispatcher_, fake_upstream_connection_));
  ASSERT_TRUE(fake_upstream_connection_->waitForNewStream(*dispatcher_, upstream_request_));
  ASSERT_TRUE(upstream_request_->waitForHeadersComplete());

  test_server_->waitForCounterGe("STR", 1);
  response->waitForReset();
  EXPECT_FALSE(response->complete());
}