TEST(HeaderMapImplTest, DoubleInlineSet) {
  HeaderMapImpl headers;
  headers.setReferenceKey(Headers::get().ContentType, "STR");
  headers.setReferenceKey(Headers::get().ContentType, "STR");
  EXPECT_EQ("STR", headers.ContentType()->value().getStringView());
  EXPECT_EQ(1UL, headers.size());
}