TEST_P(DownstreamProtocolIntegrationTest,
       OverflowDecoderBufferFromDecodeTrailersWithContinuedIteration) {
  if (downstreamProtocol() == Http::CodecType::HTTP1) {
    return;
  }
  config_helper_.setBufferLimits(64 * 1024, 64 * 1024);
  config_helper_.prependFilter(R"EOF(
  name: add-body-filter
  typed_config:
      "STR": type.googleapis.com/test.integration.filters.AddBodyFilterConfig
      where_to_add_body: DECODE_TRAILERS
      body_size: 70000
  )EOF");
  initialize();
  codec_client_ = makeHttpConnection(lookupPort("STR"));
  auto encoder_decoder =
      codec_client_->startRequest(Http::TestRequestHeaderMapImpl{{"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"}});
  auto request_encoder = &encoder_decoder.first;
  auto response = std::move(encoder_decoder.second);

  codec_client_->sendData(*request_encoder, 1024, false);
  codec_client_->sendData(*request_encoder, 1024, false);

  codec_client_->sendTrailers(*request_encoder,
                              Http::TestRequestTrailerMapImpl{{"STR"}});

  waitForNextUpstreamRequest();
  upstream_request_->encodeHeaders(Http::TestResponseHeaderMapImpl{{"STR"}}, true);
  ASSERT_TRUE(response->waitForEndStream());

  EXPECT_TRUE(upstream_request_->complete());
  EXPECT_TRUE(response->complete());
  EXPECT_EQ("STR", response->headers().getStatusValue());
}