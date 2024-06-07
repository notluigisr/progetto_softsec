TEST_P(DownstreamProtocolIntegrationTest, HittingDecoderFilterLimit) {
  config_helper_.prependFilter("STR"
                               "STR");
  config_helper_.setBufferLimits(1024, 1024);
  initialize();

  codec_client_ = makeHttpConnection(lookupPort("STR"));

  auto response = codec_client_->makeRequestWithBody(
      Http::TestRequestHeaderMapImpl{{"STR"},
                                     {"STR"},
                                     {"STR"},
                                     {"STR"},
                                     {"STR"},
                                     {"STR"}},
      1024 * 65);

  ASSERT_TRUE(response->waitForEndStream());
  
  
  
  
  if (downstream_protocol_ >= Http::CodecType::HTTP2) {
    ASSERT_TRUE(response->complete());
  }
  if (response->complete()) {
    EXPECT_EQ("STR", response->headers().getStatusValue());
  }
}