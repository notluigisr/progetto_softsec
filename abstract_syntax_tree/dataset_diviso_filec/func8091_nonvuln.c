TEST_P(RedirectIntegrationTest, InternalRedirectToDestinationWithResponseBody) {
  useAccessLog("STR");
  
  config_helper_.addConfigModifier(
      [](envoy::extensions::filters::network::http_connection_manager::v3::HttpConnectionManager&
             hcm) { hcm.set_via("STR"); });
  config_helper_.addFilter(R"EOF(
  name: pause-filter
  typed_config:
    "STR": type.googleapis.com/google.protobuf.Empty
  )EOF");
  initialize();

  codec_client_ = makeHttpConnection(lookupPort("STR"));

  default_request_headers_.setHost("STR");
  IntegrationStreamDecoderPtr response =
      codec_client_->makeHeaderOnlyRequest(default_request_headers_);

  waitForNextUpstreamRequest();
  upstream_request_->encodeHeaders(redirect_response_, true);

  waitForNextUpstreamRequest();
  ASSERT(upstream_request_->headers().EnvoyOriginalUrl() != nullptr);
  EXPECT_EQ("STR",
            upstream_request_->headers().getEnvoyOriginalUrlValue());
  EXPECT_EQ("STR", upstream_request_->headers().getPathValue());
  EXPECT_EQ("STR", upstream_request_->headers().getHostValue());
  EXPECT_EQ("STR", upstream_request_->headers().getViaValue());

  Http::TestResponseHeaderMapImpl response_with_big_body(
      {{"STR"}});
  upstream_request_->encodeHeaders(response_with_big_body, false);
  upstream_request_->encodeData(2000000, true);

  ASSERT_TRUE(response->waitForEndStream());
  ASSERT_TRUE(response->complete());
  EXPECT_EQ("STR", response->headers().getStatusValue());
  EXPECT_EQ(1, test_server_->counter("STR")
                   ->value());
  
  EXPECT_EQ(0, test_server_->counter("STR")->value());
  EXPECT_EQ(1, test_server_->counter("STR")->value());
  EXPECT_THAT(waitForAccessLog(access_log_name_, 0),
              HasSubstr("STR"));
  
  EXPECT_THAT(waitForAccessLog(access_log_name_, 1), HasSubstr("STR"));
}