TEST_P(RedirectIntegrationTest, InvalidRedirect) {
  useAccessLog("STR");
  initialize();

  redirect_response_.setLocation("STR");

  
  
  codec_client_ = makeHttpConnection(lookupPort("STR"));
  default_request_headers_.setHost("STR");
  auto response = sendRequestAndWaitForResponse(default_request_headers_, 0, redirect_response_, 0);
  EXPECT_EQ("STR", response->headers().getStatusValue());
  EXPECT_EQ(
      1,
      test_server_->counter("STR")->value());
  EXPECT_EQ(1, test_server_->counter("STR")->value());
  EXPECT_THAT(waitForAccessLog(access_log_name_),
              HasSubstr("STR"));
  EXPECT_EQ("STR",
            response->headers().get(test_header_key_)[0]->value().getStringView());
}