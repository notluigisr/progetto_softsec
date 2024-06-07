TEST_F(Http1ServerConnectionImplTest, HeaderMutateEmbeddedNul) {
  const std::string example_input = "STR";

  for (size_t n = 1; n < example_input.size(); ++n) {
    initialize();

    InSequence sequence;

    MockRequestDecoder decoder;
    EXPECT_CALL(callbacks_, newStream(_, _)).WillOnce(ReturnRef(decoder));

    Buffer::OwnedImpl buffer(
        absl::StrCat(example_input.substr(0, n), std::string(1, '\0'), example_input.substr(n)));
    EXPECT_CALL(decoder, sendLocalReply(_, _, _, _, _, _, _));
    auto status = codec_->dispatch(buffer);
    EXPECT_FALSE(status.ok());
    EXPECT_TRUE(isCodecProtocolError(status));
    EXPECT_THAT(status.message(), testing::HasSubstr("STR"));
  }
}