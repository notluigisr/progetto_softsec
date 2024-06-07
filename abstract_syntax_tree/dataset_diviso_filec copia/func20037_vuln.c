TEST(HeaderMapImplTest, InlineInsert) {
  HeaderMapImpl headers;
  EXPECT_TRUE(headers.empty());
  EXPECT_EQ(0, headers.size());
  EXPECT_EQ(nullptr, headers.Host());
  headers.insertHost().value(std::string("STR"));
  EXPECT_FALSE(headers.empty());
  EXPECT_EQ(1, headers.size());
  EXPECT_EQ("STR", headers.Host()->key().getStringView());
  EXPECT_EQ("STR", headers.Host()->value().getStringView());
  EXPECT_EQ("STR", headers.get(Headers::get().Host)->value().getStringView());
}