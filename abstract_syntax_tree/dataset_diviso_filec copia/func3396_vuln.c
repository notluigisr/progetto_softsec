TEST_P(Http2CodecImplTest, HeaderNameWithUnderscoreAreDropped) {
  headers_with_underscores_action_ = envoy::config::core::v3::HttpProtocolOptions::DROP_HEADER;
  initialize();

  TestRequestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  TestRequestHeaderMapImpl expected_headers(request_headers);
  request_headers.addCopy("STR");
  EXPECT_CALL(request_decoder_, decodeHeaders_(HeaderMapEqual(&expected_headers), _));
  request_encoder_->encodeHeaders(request_headers, false);
  EXPECT_EQ(1, stats_store_.counter("STR").value());
}