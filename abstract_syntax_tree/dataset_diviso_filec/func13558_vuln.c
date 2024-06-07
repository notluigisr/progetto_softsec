TEST_P(Http2CodecImplTest, Invalid204WithContentLength) {
  initialize();

  TestRequestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  EXPECT_CALL(request_decoder_, decodeHeaders_(_, true));
  request_encoder_->encodeHeaders(request_headers, true);

  TestResponseHeaderMapImpl response_headers{{"STR"}};
  
  
  
  
  for (unsigned i = 1; i < 3000; i++) {
    response_headers.addCopy(std::to_string(i), std::to_string(i));
  }

  EXPECT_THROW(response_encoder_->encodeHeaders(response_headers, false), ClientCodecError);
  EXPECT_EQ(1, stats_store_.counter("STR").value());
};