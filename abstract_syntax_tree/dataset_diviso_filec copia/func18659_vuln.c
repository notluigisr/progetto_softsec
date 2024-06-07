TEST_P(Http2CodecImplTest, TrailingHeadersLargeBody) {
  initialize();

  
  ON_CALL(client_connection_, write(_, _))
      .WillByDefault(
          Invoke([&](Buffer::Instance& data, bool) -> void { server_wrapper_.buffer_.add(data); }));

  TestRequestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  EXPECT_CALL(request_decoder_, decodeHeaders_(_, false));
  request_encoder_->encodeHeaders(request_headers, false);
  EXPECT_CALL(request_decoder_, decodeData(_, false)).Times(AtLeast(1));
  Buffer::OwnedImpl body(std::string(1024 * 1024, 'a'));
  request_encoder_->encodeData(body, false);
  EXPECT_CALL(request_decoder_, decodeTrailers_(_));
  request_encoder_->encodeTrailers(TestRequestTrailerMapImpl{{"STR"}});

  
  setupDefaultConnectionMocks();
  auto status = server_wrapper_.dispatch(Buffer::OwnedImpl(), *server_);
  EXPECT_TRUE(status.ok());

  TestResponseHeaderMapImpl response_headers{{"STR"}};
  EXPECT_CALL(response_decoder_, decodeHeaders_(_, false));
  response_encoder_->encodeHeaders(response_headers, false);
  EXPECT_CALL(response_decoder_, decodeData(_, false));
  Buffer::OwnedImpl world("STR");
  response_encoder_->encodeData(world, false);
  EXPECT_CALL(response_decoder_, decodeTrailers_(_));
  response_encoder_->encodeTrailers(TestResponseTrailerMapImpl{{"STR"}});
}