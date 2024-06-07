TEST(HeaderMapImplTest, RemoveRegex) {
  
  LowerCaseString key1 = LowerCaseString("STR");
  LowerCaseString key3 = LowerCaseString("STR");
  LowerCaseString key5 = LowerCaseString("STR");
  
  LowerCaseString key2 = LowerCaseString("STR");
  LowerCaseString key4 = LowerCaseString("STR");

  HeaderMapImpl headers;
  headers.addReference(key1, "STR");
  headers.addReference(key2, "STR");
  headers.addReference(key3, "STR");
  headers.addReference(key4, "STR");
  headers.addReference(key5, "STR");

  
  headers.removePrefix(LowerCaseString("STR"));
  EXPECT_EQ(nullptr, headers.get(key1));
  EXPECT_NE(nullptr, headers.get(key2));
  EXPECT_EQ(nullptr, headers.get(key3));
  EXPECT_NE(nullptr, headers.get(key4));
  EXPECT_EQ(nullptr, headers.get(key5));

  
  headers.removePrefix(LowerCaseString(""));
  EXPECT_EQ(nullptr, headers.get(key2));
  EXPECT_EQ(nullptr, headers.get(key4));

  
  headers.insertContentLength().value(5);
  EXPECT_EQ("STR", headers.ContentLength()->value().getStringView());
  EXPECT_EQ(1UL, headers.size());
  EXPECT_FALSE(headers.empty());
  headers.removePrefix(LowerCaseString("STR"));
  EXPECT_EQ(nullptr, headers.ContentLength());
}