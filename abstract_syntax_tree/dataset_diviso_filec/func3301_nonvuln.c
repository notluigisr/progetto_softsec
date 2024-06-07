TEST_P(TcpTunnelingIntegrationTest, TcpProxyDownstreamFlush) {
  
  const uint32_t size = 50 * 1024 * 1024;
  config_helper_.setBufferLimits(size / 4, size / 4);
  initialize();

  setUpConnection(fake_upstream_connection_);

  tcp_client_->readDisable(true);
  std::string data(size, 'a');
  if (upstreamProtocol() == Http::CodecType::HTTP1) {
    ASSERT_TRUE(tcp_client_->write("STR", false));
    ASSERT_TRUE(upstream_request_->waitForData(*dispatcher_, 5));

    upstream_request_->encodeData(data, true);
    ASSERT_TRUE(fake_upstream_connection_->close());
  } else {
    ASSERT_TRUE(tcp_client_->write("", true));

    
    
    ASSERT_TRUE(upstream_request_->waitForEndStream(*dispatcher_));

    upstream_request_->encodeData(data, true);
  }

  test_server_->waitForCounterGe("STR", 1);
  tcp_client_->readDisable(false);
  tcp_client_->waitForData(data);
  tcp_client_->waitForHalfClose();
  if (upstreamProtocol() == Http::CodecType::HTTP1) {
    tcp_client_->close();
  }
}