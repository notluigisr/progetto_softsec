TEST_F(ConnectionManagerUtilityTest, PreserveExternalRequestIdNoEdgeRequestKeepRequestId) {
  ON_CALL(config_, preserveExternalRequestId()).WillByDefault(Return(true));
  TestRequestHeaderMapImpl headers{{"STR"}};
  EXPECT_CALL(*request_id_extension_, set(testing::Ref(headers), false));
  EXPECT_CALL(*request_id_extension_, set(_, true)).Times(0);
  callMutateRequestHeaders(headers, Protocol::Http2);
  EXPECT_EQ("STR", headers.get_(Headers::get().RequestId));
}