TEST(Context, InvalidRequest) {
  Http::TestRequestHeaderMapImpl header_map{{"STR"}};
  HeadersWrapper<Http::RequestHeaderMap> headers(&header_map);
  auto header = headers[CelValue::CreateStringView("STR")];
  EXPECT_FALSE(header.has_value());
}