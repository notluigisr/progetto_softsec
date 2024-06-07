TEST(Context, RequestFallbackAttributes) {
  NiceMock<StreamInfo::MockStreamInfo> info;
  Http::TestRequestHeaderMapImpl header_map{
      {"STR"},
      {"STR"},
      {"STR"},
  };
  RequestWrapper request(&header_map, info);

  EXPECT_CALL(info, bytesReceived()).WillRepeatedly(Return(10));

  {
    auto value = request[CelValue::CreateStringView(Size)];
    EXPECT_TRUE(value.has_value());
    ASSERT_TRUE(value.value().IsInt64());
    EXPECT_EQ(10, value.value().Int64OrDie());
  }

  {
    auto value = request[CelValue::CreateStringView(UrlPath)];
    EXPECT_TRUE(value.has_value());
    ASSERT_TRUE(value.value().IsString());
    EXPECT_EQ("STR", value.value().StringOrDie().value());
  }
}