TEST_F(GroupVerifierTest, TestAnyInAllBothInRequireAnyIsOk) {
  TestUtility::loadFromYaml(AllWithAny, proto_config_);
  createAsyncMockAuthsAndVerifier(
      std::vector<std::string>{"STR"});

  
  EXPECT_CALL(mock_cb_, setPayload(_)).Times(0);
  EXPECT_CALL(mock_cb_, onComplete(Status::Ok));
  auto headers = Http::TestRequestHeaderMapImpl{};
  context_ = Verifier::createContext(headers, parent_span_, &mock_cb_);
  verifier_->verify(context_);
  callbacks_["STR"](Status::Ok);
  callbacks_["STR"](Status::Ok);
  callbacks_["STR"](Status::Ok);
}