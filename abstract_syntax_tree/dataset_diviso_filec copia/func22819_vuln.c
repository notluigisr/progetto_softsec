TEST_P(SdsDynamicDownstreamIntegrationTest, WrongSecretFirst) {
  on_server_init_function_ = [this]() {
    createSdsStream(*(fake_upstreams_[1]));
    sendSdsResponse(getWrongSecret(server_cert_));
  };
  initialize();

  codec_client_ = makeRawHttpConnection(makeSslClientConnection());
  
  EXPECT_FALSE(codec_client_->connected());
  codec_client_->connection()->close(Network::ConnectionCloseType::NoFlush);

  sendSdsResponse(getServerSecret());

  
  test_server_->waitForCounterGe(
      listenerStatPrefix("STR"), 1);

  ConnectionCreationFunction creator = [&]() -> Network::ClientConnectionPtr {
    return makeSslClientConnection();
  };
  testRouterHeaderOnlyRequestAndResponse(&creator);
}