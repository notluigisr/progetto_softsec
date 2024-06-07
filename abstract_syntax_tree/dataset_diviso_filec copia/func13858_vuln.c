TEST_F(OAuth2Test, OAuthBearerTokenFlowFromHeader) {
  Http::TestRequestHeaderMapImpl request_headers_before{
      {Http::Headers::get().Path.get(), "STR"},
      {Http::Headers::get().Host.get(), "STR"},
      {Http::Headers::get().Method.get(), Http::Headers::get().MethodValues.Get},
      {Http::Headers::get().Scheme.get(), "STR"},
      {Http::CustomHeaders::get().Authorization.get(), "STR"},
  };
  
  Http::TestRequestHeaderMapImpl request_headers_after{
      {Http::Headers::get().Path.get(), "STR"},
      {Http::Headers::get().Host.get(), "STR"},
      {Http::Headers::get().Method.get(), Http::Headers::get().MethodValues.Get},
      {Http::Headers::get().Scheme.get(), "STR"},
      {Http::CustomHeaders::get().Authorization.get(), "STR"},
  };

  
  EXPECT_CALL(*validator_, setParams(_, _));
  EXPECT_CALL(*validator_, isValid()).WillOnce(Return(false));

  EXPECT_EQ(Http::FilterHeadersStatus::Continue,
            filter_->decodeHeaders(request_headers_before, false));

  
  EXPECT_EQ(request_headers_before, request_headers_after);
}