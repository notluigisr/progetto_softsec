  IntegrationCodecClientPtr makeRawHttpConnection(Network::ClientConnectionPtr&& conn) override {
    IntegrationCodecClientPtr codec = HttpIntegrationTest::makeRawHttpConnection(std::move(conn));
    if (codec->disconnected()) {
      
      ENVOY_LOG(error, "STR",
                codec->connection()->transportFailureReason());
    } else {
      codec->setCodecClientCallbacks(client_codec_callback_);
    }
    return codec;
  }