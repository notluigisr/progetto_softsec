TEST_P(QuicHttpIntegrationTest, StopAcceptingConnectionsWhenOverloaded) {
  initialize();
  fake_upstreams_[0]->set_allow_unexpected_disconnects(true);

  
  updateResource(0.9);
  test_server_->waitForGaugeEq("STR",
                               1);
  codec_client_ = makeRawHttpConnection(makeClientConnection((lookupPort("STR"))));
  EXPECT_TRUE(codec_client_->disconnected());

  
  updateResource(0.8);
  test_server_->waitForGaugeEq("STR",
                               0);
  codec_client_ = makeHttpConnection(makeClientConnection((lookupPort("STR"))));
  auto response = codec_client_->makeHeaderOnlyRequest(default_request_headers_);
  waitForNextUpstreamRequest(0);
  
  upstream_request_->encodeHeaders(default_response_headers_, false);

  updateResource(0.95);
  test_server_->waitForGaugeEq("STR", 1);
  
  upstream_request_->encodeData(10, true);
  response->waitForEndStream();
  EXPECT_TRUE(response->complete());
  EXPECT_EQ("STR", response->headers().getStatusValue());

  
  auto response2 = codec_client_->makeHeaderOnlyRequest(default_request_headers_);
  response2->waitForEndStream();
  EXPECT_EQ("STR", response2->headers().getStatusValue());
  EXPECT_EQ("STR", response2->body());
  codec_client_->close();

  EXPECT_TRUE(makeRawHttpConnection(makeClientConnection((lookupPort("STR"))))->disconnected());
}