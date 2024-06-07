TEST_F(ConnectionManagerUtilityTest, NonTlsSanitizeClientCertWhenForward) {
  ON_CALL(connection_, ssl()).WillByDefault(Return(nullptr));
  ON_CALL(config_, forwardClientCert())
      .WillByDefault(Return(Http::ForwardClientCertType::ForwardOnly));
  std::vector<Http::ClientCertDetailsType> details;
  ON_CALL(config_, setCurrentClientCertDetails()).WillByDefault(ReturnRef(details));
  TestRequestHeaderMapImpl headers{{"STR"}};

  EXPECT_EQ((MutateRequestRet{"STR", false, Tracing::Reason::NotTraceable}),
            callMutateRequestHeaders(headers, Protocol::Http2));
  EXPECT_FALSE(headers.has("STR"));
}