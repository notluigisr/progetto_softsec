TEST_F(OAuth2Test, OAuthTestFullFlowPostWithParameters) {
  
  Http::TestRequestHeaderMapImpl first_request_headers{
      {Http::Headers::get().Path.get(), "STR"},
      {Http::Headers::get().Host.get(), "STR"},
      {Http::Headers::get().Method.get(), Http::Headers::get().MethodValues.Post},
      {Http::Headers::get().Scheme.get(), "STR"},
  };

  
  Http::TestResponseHeaderMapImpl first_response_headers{
      {Http::Headers::get().Status.get(), "STR"},
      {Http::Headers::get().Location.get(),
       "STR"
       "STR" +
           TEST_CLIENT_ID + "STR" + TEST_ENCODED_AUTH_SCOPES +
           "STR"
           "STR"
           "STR"
           "STR"
           "STR"
           "STR"},
  };

  
  EXPECT_CALL(*validator_, setParams(_, _));
  EXPECT_CALL(*validator_, isValid()).WillOnce(Return(false));

  
  EXPECT_CALL(decoder_callbacks_, encodeHeaders_(HeaderMapEqualRef(&first_response_headers), true));

  
  EXPECT_EQ(Http::FilterHeadersStatus::StopIteration,
            filter_->decodeHeaders(first_request_headers, false));

  
  Http::TestRequestHeaderMapImpl second_request_headers{
      {Http::Headers::get().Path.get(), "STR"
                                        "STR"},
      {Http::Headers::get().Host.get(), "STR"},
      {Http::Headers::get().Method.get(), Http::Headers::get().MethodValues.Get},
      {Http::Headers::get().Scheme.get(), "STR"},
  };

  
  EXPECT_CALL(*validator_, setParams(_, _));
  EXPECT_CALL(*validator_, isValid()).WillOnce(Return(false));

  EXPECT_CALL(*oauth_client_, asyncGetAccessToken("STR",
                                                  "STR" + TEST_CALLBACK));

  
  EXPECT_EQ(Http::FilterHeadersStatus::StopAllIterationAndBuffer,
            filter_->decodeHeaders(second_request_headers, false));

  EXPECT_EQ(1, config_->stats().oauth_unauthorized_rq_.value());
  EXPECT_EQ(config_->clusterName(), "STR");

  
  
  Http::TestRequestHeaderMapImpl second_response_headers{
      {Http::Headers::get().Status.get(), "STR"},
      {Http::Headers::get().SetCookie.get(),
       "STR"
       "STR"
       "STR"},
      {Http::Headers::get().SetCookie.get(),
       "STR"},
      {Http::Headers::get().SetCookie.get(), "STR"},
      {Http::Headers::get().Location.get(),
       "STR"},
  };

  EXPECT_CALL(decoder_callbacks_,
              encodeHeaders_(HeaderMapEqualRef(&second_response_headers), true));
  EXPECT_CALL(decoder_callbacks_, continueDecoding());

  filter_->finishFlow();
}