TEST_P(Http2CodecImplTest, ShutdownNotice) {
  initialize();

  TestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  EXPECT_CALL(request_decoder_, decodeHeaders_(_, true));
  request_encoder_->encodeHeaders(request_headers, true);

  EXPECT_CALL(client_callbacks_, onGoAway());
  server_->shutdownNotice();
  server_->goAway();

  TestHeaderMapImpl response_headers{{"STR"}};
  EXPECT_CALL(response_decoder_, decodeHeaders_(_, true));
  response_encoder_->encodeHeaders(response_headers, true);
}