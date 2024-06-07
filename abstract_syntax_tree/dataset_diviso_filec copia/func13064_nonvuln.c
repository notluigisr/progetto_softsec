TEST_F(ConnectionManagerUtilityTest, MergeSlashesDefaultOff) {
  ON_CALL(config_, shouldNormalizePath()).WillByDefault(Return(true));
  ON_CALL(config_, shouldMergeSlashes()).WillByDefault(Return(false));
  TestRequestHeaderMapImpl original_headers;
  original_headers.setPath("STR");

  TestRequestHeaderMapImpl header_map(original_headers);
  ConnectionManagerUtility::maybeNormalizePath(header_map, config_);
  EXPECT_EQ(header_map.getPathValue(), "STR");
}