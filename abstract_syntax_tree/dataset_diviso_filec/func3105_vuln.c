TEST_P(Http2CodecImplTest, InvalidHeadersFrame) {
  initialize();

  EXPECT_THROW(request_encoder_->encodeHeaders(TestRequestHeaderMapImpl{}, true), ServerCodecError);
  EXPECT_EQ(1, stats_store_.counter("STR").value());
}