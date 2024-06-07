TEST_F(OAuth2Test, OAuthCallbackStartsAuthentication) {
  Http::TestRequestHeaderMapImpl request_headers{
      {Http::Headers::get().Path.get(), "STR"},
      {Http::Headers::get().Host.get(), "STR"},
      {Http::Headers::get().Scheme.get(), "STR"},
      {Http::Headers::get().Method.get(), Http::Headers::get().MethodValues.Get},
  };

  
  EXPECT_CALL(*validator_, setParams(_, _));
  EXPECT_CALL(*validator_, isValid()).WillOnce(Return(false));

  EXPECT_CALL(*oauth_client_, asyncGetAccessToken("STR",
                                                  "STR" + TEST_CALLBACK));

  EXPECT_EQ(Http::FilterHeadersStatus::StopAllIterationAndBuffer,
            filter_->decodeHeaders(request_headers, false));
}