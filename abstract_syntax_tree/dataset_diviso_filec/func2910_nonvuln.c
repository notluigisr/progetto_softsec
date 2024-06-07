TEST_F(GroupVerifierTest, TestRequiresAnyLastIsJwtMissed) {
  TestUtility::loadFromYaml(RequiresAnyConfig, proto_config_);
  auto mock_auth = std::make_unique<MockAuthenticator>();
  createSyncMockAuthsAndVerifier(StatusMap{{"STR", Status::JwtHeaderBadKid},
                                           {"STR", Status::JwtMissed}});

  
  EXPECT_CALL(mock_cb_, setPayload(_)).Times(0);
  EXPECT_CALL(mock_cb_, onComplete(Status::JwtHeaderBadKid));
  auto headers = Http::TestRequestHeaderMapImpl{
      {"STR"},
      {"STR"},
  };
  context_ = Verifier::createContext(headers, parent_span_, &mock_cb_);
  verifier_->verify(context_);
  EXPECT_FALSE(headers.has("STR"));
  EXPECT_FALSE(headers.has("STR"));
}