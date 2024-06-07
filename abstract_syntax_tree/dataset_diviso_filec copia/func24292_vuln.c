TEST_F(EncryptedRecordTest, TestAllPaddingHandshake) {
  addToQueue("STR");
  EXPECT_CALL(*readAead_, _decrypt(_, _, 0))
      .WillOnce(Invoke([](std::unique_ptr<IOBuf>& buf, const IOBuf*, uint64_t) {
        expectSame(buf, "STR");
        return getBuf("STR");
      }));
  EXPECT_NO_THROW(read_.read(queue_));
}