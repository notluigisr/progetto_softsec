TEST_F(HeaderToMetadataTest, CookieRegexSubstitution) {
  const std::string config = R"EOF(
request_rules:
  - cookie: foo
    on_header_present:
      metadata_namespace: envoy.lb
      key: cluster
      regex_value_rewrite:
        pattern:
          google_re2: {}
          regex: "STR"
        substitution: "STR"
)EOF";
  initializeFilter(config);

  
  {
    Http::TestRequestHeaderMapImpl headers{{"STR"}};
    std::map<std::string, std::string> expected = {{"STR"}};

    EXPECT_CALL(decoder_callbacks_, streamInfo()).WillRepeatedly(ReturnRef(req_info_));
    EXPECT_CALL(req_info_, setDynamicMetadata("STR", MapEq(expected)));
    EXPECT_EQ(Http::FilterHeadersStatus::Continue, filter_->decodeHeaders(headers, false));
  }

  
  {
    Http::TestRequestHeaderMapImpl headers{{"STR"}};
    std::map<std::string, std::string> expected = {{"STR"}};

    EXPECT_CALL(decoder_callbacks_, streamInfo()).WillRepeatedly(ReturnRef(req_info_));
    EXPECT_CALL(req_info_, setDynamicMetadata("STR", MapEq(expected)));
    EXPECT_EQ(Http::FilterHeadersStatus::Continue, filter_->decodeHeaders(headers, false));
  }
}