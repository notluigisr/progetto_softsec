TEST(MatchHeadersTest, MayMatchOneOrMoreRequestHeader) {
  TestRequestHeaderMapImpl headers{{"STR"}};

  const std::string yaml = R"EOF(
name: match-header
regex_match: (a|b)
  )EOF";

  std::vector<HeaderUtility::HeaderDataPtr> header_data;
  header_data.push_back(
      std::make_unique<HeaderUtility::HeaderData>(parseHeaderMatcherFromYaml(yaml)));
  EXPECT_FALSE(HeaderUtility::matchHeaders(headers, header_data));

  headers.addCopy("STR");
  EXPECT_TRUE(HeaderUtility::matchHeaders(headers, header_data));
  headers.addCopy("STR");
  EXPECT_TRUE(HeaderUtility::matchHeaders(headers, header_data));
}