TEST_P(Http2CodecImplTest, InvalidRepeatContinueAllowed) {
  stream_error_on_invalid_http_messaging_ = true;
  initialize();

  MockStreamCallbacks request_callbacks;
  request_encoder_->getStream().addCallbacks(request_callbacks);

  TestRequestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  EXPECT_CALL(request_decoder_, decodeHeaders_(_, true));
  request_encoder_->encodeHeaders(request_headers, true);

  TestResponseHeaderMapImpl continue_headers{{"STR"}};
  EXPECT_CALL(response_decoder_, decode100ContinueHeaders_(_));
  response_encoder_->encode100ContinueHeaders(continue_headers);

  
  ON_CALL(server_connection_, write(_, _))
      .WillByDefault(
          Invoke([&](Buffer::Instance& data, bool) -> void { client_wrapper_.buffer_.add(data); }));

  response_encoder_->encodeHeaders(continue_headers, true);

  
  EXPECT_CALL(request_callbacks, onResetStream(StreamResetReason::LocalReset, _));
  setupDefaultConnectionMocks();
  auto status = client_wrapper_.dispatch(Buffer::OwnedImpl(), *client_);
  EXPECT_TRUE(status.ok());

  EXPECT_EQ(1, stats_store_.counter("STR").value());
  expectDetailsRequest("STR");
};