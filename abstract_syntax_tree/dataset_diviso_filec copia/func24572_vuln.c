TEST_P(Http2CodecImplTest, TestLargeRequestHeadersAtLimitAccepted) {
  uint32_t codec_limit_kb = 64;
  max_request_headers_kb_ = codec_limit_kb;
  initialize();

  TestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  std::string key = "STR";
  uint32_t head_room = 77;
  uint32_t long_string_length =
      codec_limit_kb * 1024 - request_headers.byteSize() - key.length() - head_room;
  std::string long_string = std::string(long_string_length, 'q');
  request_headers.addCopy(key, long_string);

  
  
  
  ASSERT_EQ(request_headers.byteSize() + head_room, codec_limit_kb * 1024);

  EXPECT_CALL(request_decoder_, decodeHeaders_(_, _));
  request_encoder_->encodeHeaders(request_headers, true);
}