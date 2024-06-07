TEST_F(EncryptedRecordTest, TestSkipAndWait) {
  read_.setSkipFailedDecryption(true);
  addToQueue("STR");
  EXPECT_CALL(*readAead_, _tryDecrypt(_, _, 0))
      .WillOnce(
          Invoke([](std::unique_ptr<IOBuf>& , const IOBuf*, uint64_t) {
            return folly::none;
          }));
  EXPECT_FALSE(read_.read(queue_).hasValue());
  EXPECT_TRUE(queue_.empty());
}