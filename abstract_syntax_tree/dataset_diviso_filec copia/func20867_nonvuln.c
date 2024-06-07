TEST_F(RouterTest, Redirect) {
  MockDirectResponseEntry direct_response;
  std::string route_name("STR");
  EXPECT_CALL(direct_response, newPath(_)).WillOnce(Return("STR"));
  EXPECT_CALL(direct_response, routeName()).WillOnce(ReturnRef(route_name));
  EXPECT_CALL(direct_response, rewritePathHeader(_, _));
  EXPECT_CALL(direct_response, responseCode()).WillRepeatedly(Return(Http::Code::MovedPermanently));
  EXPECT_CALL(direct_response, responseBody()).WillOnce(ReturnRef(EMPTY_STRING));
  EXPECT_CALL(direct_response, finalizeResponseHeaders(_, _));
  EXPECT_CALL(*callbacks_.route_, directResponseEntry()).WillRepeatedly(Return(&direct_response));
  absl::string_view route_name_view(route_name);
  EXPECT_CALL(callbacks_.stream_info_, setRouteName(route_name_view));

  Http::TestResponseHeaderMapImpl response_headers{{"STR"}};
  EXPECT_CALL(callbacks_, encodeHeaders_(HeaderMapEqualRef(&response_headers), true));
  Http::TestRequestHeaderMapImpl headers;
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, true);
  EXPECT_EQ(0U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());
  EXPECT_FALSE(callbacks_.stream_info_.attemptCount().has_value());
  EXPECT_TRUE(verifyHostUpstreamStats(0, 0));
}