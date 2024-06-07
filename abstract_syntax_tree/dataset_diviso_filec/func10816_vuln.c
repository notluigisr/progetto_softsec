TEST(HeaderMapImplTest, DoubleInlineAdd) {
  {
    HeaderMapImpl headers;
    const std::string foo("STR");
    const std::string bar("STR");
    headers.addReference(Headers::get().ContentLength, foo);
    headers.addReference(Headers::get().ContentLength, bar);
    EXPECT_EQ("STR", headers.ContentLength()->value().getStringView());
    EXPECT_EQ(1UL, headers.size());
  }
  {
    HeaderMapImpl headers;
    headers.addReferenceKey(Headers::get().ContentLength, "STR");
    headers.addReferenceKey(Headers::get().ContentLength, "STR");
    EXPECT_EQ("STR", headers.ContentLength()->value().getStringView());
    EXPECT_EQ(1UL, headers.size());
  }
  {
    HeaderMapImpl headers;
    headers.addReferenceKey(Headers::get().ContentLength, 5);
    headers.addReferenceKey(Headers::get().ContentLength, 6);
    EXPECT_EQ("STR", headers.ContentLength()->value().getStringView());
    EXPECT_EQ(1UL, headers.size());
  }
  {
    HeaderMapImpl headers;
    const std::string foo("STR");
    headers.addReference(Headers::get().ContentLength, foo);
    headers.addReferenceKey(Headers::get().ContentLength, 6);
    EXPECT_EQ("STR", headers.ContentLength()->value().getStringView());
    EXPECT_EQ(1UL, headers.size());
  }
}