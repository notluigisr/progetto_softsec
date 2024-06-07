TEST_P(TcpTunnelingIntegrationTest, NoDataTransmittedIfConnectFailureResponseIsReceived) {
  initialize();

  
  tcp_client_ = makeTcpConnection(lookupPort("STR"));

  
  ASSERT_TRUE(tcp_client_->write("STR", false));

  ASSERT_TRUE(fake_upstreams_[0]->waitForHttpConnection(*dispatcher_, fake_upstream_connection_));
  ASSERT_TRUE(fake_upstream_connection_->waitForNewStream(*dispatcher_, upstream_request_));
  ASSERT_TRUE(upstream_request_->waitForHeadersComplete());

  default_response_headers_.setStatus(enumToInt(Http::Code::ServiceUnavailable));
  upstream_request_->encodeHeaders(default_response_headers_, false);

  
  ASSERT_FALSE(upstream_request_->waitForData(*dispatcher_, 1, std::chrono::milliseconds(100)));

  tcp_client_->close();
  if (upstreamProtocol() == Http::CodecType::HTTP1) {
    ASSERT_TRUE(fake_upstream_connection_->waitForDisconnect());
  } else {
    ASSERT_TRUE(upstream_request_->waitForReset());
  }
}