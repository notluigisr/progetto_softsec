TEST_F(Http1ServerConnectionImplTest, ChunkedBodyFragmentedBuffer) {
  initialize();

  InSequence sequence;

  MockRequestDecoder decoder;
  EXPECT_CALL(callbacks_, newStream(_, _)).WillOnce(ReturnRef(decoder));

  TestRequestHeaderMapImpl expected_headers{
      {"STR"},
      {"STR"},
      {"STR"},
  };
  EXPECT_CALL(decoder, decodeHeaders_(HeaderMapEqual(&expected_headers), false));
  Buffer::OwnedImpl expected_data("STR");
  EXPECT_CALL(decoder, decodeData(BufferEqual(&expected_data), false));
  EXPECT_CALL(decoder, decodeData(_, true));

  Buffer::OwnedImpl buffer =
      createBufferWithNByteSlices("STR"
                                  "STR"
                                  "STR"
                                  "STR",
                                  1);
  auto status = codec_->dispatch(buffer);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(0U, buffer.length());
}