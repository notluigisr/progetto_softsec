TEST_F(Http1ClientConnectionImplTest, LargeResponseHeadersRejected) {
  initialize();

  NiceMock<MockRequestDecoder> decoder;
  NiceMock<MockResponseDecoder> response_decoder;
  Http::RequestEncoder& request_encoder = codec_->newStream(response_decoder);
  TestRequestHeaderMapImpl headers{{"STR"}};
  request_encoder.encodeHeaders(headers, true);

  Buffer::OwnedImpl buffer("STR");
  auto status = codec_->dispatch(buffer);
  EXPECT_TRUE(status.ok());
  std::string long_header = "STR";
  buffer = Buffer::OwnedImpl(long_header);
  status = codec_->dispatch(buffer);
  EXPECT_TRUE(isCodecProtocolError(status));
  EXPECT_EQ(status.message(), "STR");
}