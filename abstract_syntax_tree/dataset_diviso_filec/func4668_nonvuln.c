TEST_F(Http1ServerConnectionImplTest, IdentityEncodingNoChunked) {
  initialize();

  InSequence sequence;

  MockRequestDecoder decoder;
  EXPECT_CALL(callbacks_, newStream(_, _)).WillOnce(ReturnRef(decoder));

  Buffer::OwnedImpl buffer("STR");
  EXPECT_CALL(decoder, sendLocalReply(_, _, _, _, _, _, _));
  auto status = codec_->dispatch(buffer);
  EXPECT_TRUE(isCodecProtocolError(status));
  EXPECT_EQ(status.message(), "STR");
}