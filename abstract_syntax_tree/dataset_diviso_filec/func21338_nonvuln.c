TEST(MatchHeadersTest, HeaderRangeInverseMatch) {
  TestRequestHeaderMapImpl matching_headers{{"STR"},
                                            {"STR"},
                                            {"STR"},
                                            {"STR"}};
  TestRequestHeaderMapImpl unmatching_headers{{"STR"}};

  const std::string yaml = R"EOF(
name: match-header
range_match:
  start: -10
  end: 0
invert_match: true
  )EOF";

  std::vector<HeaderUtility::HeaderDataPtr> header_data;
  header_data.push_back(
      std::make_unique<HeaderUtility::HeaderData>(parseHeaderMatcherFromYaml(yaml)));
  EXPECT_TRUE(HeaderUtility::matchHeaders(matching_headers, header_data));
  EXPECT_FALSE(HeaderUtility::matchHeaders(unmatching_headers, header_data));
}