TEST(HeaderMapImplTest, AddCopy) {
  HeaderMapImpl headers;

  
  std::unique_ptr<LowerCaseString> lcKeyPtr(new LowerCaseString("STR"));
  headers.addCopy(*lcKeyPtr, "STR");

  const HeaderString& value = headers.get(*lcKeyPtr)->value();

  EXPECT_EQ("STR", value.getStringView());
  EXPECT_EQ(5UL, value.size());

  lcKeyPtr.reset();

  const HeaderString& value2 = headers.get(LowerCaseString("STR"))->value();

  EXPECT_EQ("STR", value2.getStringView());
  EXPECT_EQ(5UL, value2.size());
  EXPECT_EQ(value.getStringView(), value2.getStringView());
  EXPECT_EQ(1UL, headers.size());

  
  
  
  
  headers.remove(LowerCaseString("STR"));

  
  
  lcKeyPtr = std::make_unique<LowerCaseString>(std::string("STR");
  EXPECT_STREQ("STR", lcKeyPtr->get().c_str());

  headers.addCopy(*lcKeyPtr, 42);

  const HeaderString& value3 = headers.get(*lcKeyPtr)->value();

  EXPECT_EQ("STR", value3.getStringView());
  EXPECT_EQ(2UL, value3.size());

  lcKeyPtr.reset();

  const HeaderString& value4 = headers.get(LowerCaseString("STR"))->value();

  EXPECT_EQ("STR", value4.getStringView());
  EXPECT_EQ(2UL, value4.size());
  EXPECT_EQ(1UL, headers.size());

  
  LowerCaseString lcKey3(std::string("STR");
  EXPECT_STREQ("STR", lcKey3.get().c_str());

  EXPECT_EQ("STR", headers.get(lcKey3)->value().getStringView());
  EXPECT_EQ(2UL, headers.get(lcKey3)->value().size());

  LowerCaseString cache_control("STR");
  headers.addCopy(cache_control, "STR");
  EXPECT_EQ("STR", headers.get(cache_control)->value().getStringView());
  EXPECT_EQ("STR", headers.CacheControl()->value().getStringView());
  headers.addCopy(cache_control, "STR");
  EXPECT_EQ("STR", headers.get(cache_control)->value().getStringView());
  headers.addCopy(cache_control, "");
  EXPECT_EQ("STR", headers.get(cache_control)->value().getStringView());
  headers.addCopy(cache_control, 123);
  EXPECT_EQ("STR", headers.get(cache_control)->value().getStringView());
  headers.addCopy(cache_control, std::numeric_limits<uint64_t>::max());
  EXPECT_EQ("STR",
            headers.get(cache_control)->value().getStringView());
}