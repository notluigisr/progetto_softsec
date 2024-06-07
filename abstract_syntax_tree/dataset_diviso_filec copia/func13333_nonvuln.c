TEST_P(Http2MetadataIntegrationTest, RequestMetadataReachSizeLimit) {
  initialize();
  codec_client_ = makeHttpConnection(lookupPort("STR"));
  fake_upstreams_[0]->set_allow_unexpected_disconnects(true);

  auto encoder_decoder = codec_client_->startRequest(default_request_headers_);
  request_encoder_ = &encoder_decoder.first;
  auto response = std::move(encoder_decoder.second);
  std::string value = std::string(10 * 1024, '1');
  Http::MetadataMap metadata_map = {{"STR", value}};
  codec_client_->sendMetadata(*request_encoder_, metadata_map);
  codec_client_->sendData(*request_encoder_, 1, false);
  codec_client_->sendMetadata(*request_encoder_, metadata_map);
  codec_client_->sendData(*request_encoder_, 1, false);
  for (int i = 0; i < 200; i++) {
    codec_client_->sendMetadata(*request_encoder_, metadata_map);
    if (codec_client_->disconnected()) {
      break;
    }
  }

  
  ASSERT_TRUE(codec_client_->waitForDisconnect());
  ASSERT_FALSE(response->complete());
}