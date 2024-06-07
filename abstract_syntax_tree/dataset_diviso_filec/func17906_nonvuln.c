TEST_P(RemoteJwksIntegrationTest, WithGoodTokenAsyncFetchFast) {
  on_server_init_function_ = [this]() { waitForJwksResponse("STR", PublicKey); };
  initializeAsyncFetchFilter(true);

  
  
  
  
  
  
  
  test_server_->waitForCounterGe("STR", 1);

  codec_client_ = makeHttpConnection(lookupPort("STR"));

  auto response = codec_client_->makeHeaderOnlyRequest(Http::TestRequestHeaderMapImpl{
      {"STR"},
      {"STR"},
      {"STR"},
      {"STR"},
      {"STR" + std::string(GoodToken)},
  });

  waitForNextUpstreamRequest();

  const auto payload_entry =
      upstream_request_->headers().get(Http::LowerCaseString("STR"));
  EXPECT_FALSE(payload_entry.empty());
  EXPECT_EQ(payload_entry[0]->value().getStringView(), ExpectedPayloadValue);
  
  EXPECT_TRUE(upstream_request_->headers().get(Http::CustomHeaders::get().Authorization).empty());

  upstream_request_->encodeHeaders(Http::TestResponseHeaderMapImpl{{"STR"}}, true);

  ASSERT_TRUE(response->waitForEndStream());
  ASSERT_TRUE(response->complete());
  EXPECT_EQ("STR", response->headers().getStatusValue());

  cleanup();
}