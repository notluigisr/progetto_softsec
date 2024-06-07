TEST_P(Http2CodecImplTest, Invalid204WithContentLengthAllowed) {
  stream_error_on_invalid_http_messaging_ = true;
  initialize();

  MockStreamCallbacks request_callbacks;
  request_encoder_->getStream().addCallbacks(request_callbacks);

  TestRequestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  EXPECT_CALL(request_decoder_, decodeHeaders_(_, true));
  request_encoder_->encodeHeaders(request_headers, true);

  
  ON_CALL(server_connection_, write(_, _))
      .WillByDefault(
          Invoke([&](Buffer::Instance& data, bool) -> void { client_wrapper_.buffer_.add(data); }));

  TestResponseHeaderMapImpl response_headers{{"STR"}};
  
  
  
  
  for (int i = 1; i < 3000; i++) {
    response_headers.addCopy(std::to_string(i), std::to_string(i));
  }

  response_encoder_->encodeHeaders(response_headers, false);

  
  EXPECT_CALL(request_callbacks, onResetStream(StreamResetReason::LocalReset, _));
  EXPECT_CALL(server_stream_callbacks_, onResetStream(StreamResetReason::RemoteReset, _));
  setupDefaultConnectionMocks();
  auto status = client_wrapper_.dispatch(Buffer::OwnedImpl(), *client_);
  EXPECT_TRUE(status.ok());

  EXPECT_EQ(1, stats_store_.counter("STR").value());
  expectDetailsRequest("STR");
};