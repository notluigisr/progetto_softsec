TEST(HeaderMapImplTest, Remove) {
  HeaderMapImpl headers;

  
  LowerCaseString static_key("STR");
  std::string ref_value("STR");
  headers.addReference(static_key, ref_value);
  EXPECT_EQ("STR", headers.get(static_key)->value().getStringView());
  EXPECT_EQ(HeaderString::Type::Reference, headers.get(static_key)->value().type());
  EXPECT_EQ(1UL, headers.size());
  EXPECT_FALSE(headers.empty());
  headers.remove(static_key);
  EXPECT_EQ(nullptr, headers.get(static_key));
  EXPECT_EQ(0UL, headers.size());
  EXPECT_TRUE(headers.empty());

  
  headers.insertContentLength().value(5);
  EXPECT_EQ("STR", headers.ContentLength()->value().getStringView());
  EXPECT_EQ(1UL, headers.size());
  EXPECT_FALSE(headers.empty());
  headers.removeContentLength();
  EXPECT_EQ(nullptr, headers.ContentLength());
  EXPECT_EQ(0UL, headers.size());
  EXPECT_TRUE(headers.empty());

  
  headers.insertContentLength().value(5);
  EXPECT_EQ("STR", headers.ContentLength()->value().getStringView());
  EXPECT_EQ(1UL, headers.size());
  EXPECT_FALSE(headers.empty());
  headers.remove(Headers::get().ContentLength);
  EXPECT_EQ(nullptr, headers.ContentLength());
  EXPECT_EQ(0UL, headers.size());
  EXPECT_TRUE(headers.empty());
}