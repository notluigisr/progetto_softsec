TEST_F(GroupVerifierTest, TestRequiresAnyWithAllowMissingButOk) {
  TestUtility::loadFromYaml(RequiresAnyConfig, proto_config_);
  proto_config_.mutable_rules(0)
      ->mutable_requires()
      ->mutable_requires_any()
      ->add_requirements()
      ->mutable_allow_missing();

  createAsyncMockAuthsAndVerifier(std::vector<std::string>{"STR"});
  EXPECT_CALL(mock_cb_, onComplete(Status::Ok));

  auto headers = Http::TestRequestHeaderMapImpl{};
  context_ = Verifier::createContext(headers, parent_span_, &mock_cb_);
  verifier_->verify(context_);
  callbacks_["STR"](Status::JwtMissed);
  callbacks_["STR"](Status::JwtUnknownIssuer);
}