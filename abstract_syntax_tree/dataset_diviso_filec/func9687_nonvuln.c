TEST_F(GroupVerifierTest, TestRequiresAllBothFailed) {
  TestUtility::loadFromYaml(RequiresAllConfig, proto_config_);
  createAsyncMockAuthsAndVerifier(std::vector<std::string>{"STR"});

  
  EXPECT_CALL(mock_cb_, setPayload(_)).Times(0);
  EXPECT_CALL(mock_cb_, onComplete(Status::JwtUnknownIssuer));
  auto headers = Http::TestRequestHeaderMapImpl{
      {"STR"},
      {"STR"},
  };
  context_ = Verifier::createContext(headers, parent_span_, &mock_cb_);
  verifier_->verify(context_);
  EXPECT_FALSE(headers.has("STR"));
  EXPECT_FALSE(headers.has("STR"));
  callbacks_["STR"](Status::JwtUnknownIssuer);
  callbacks_["STR"](Status::JwtUnknownIssuer);
}