TEST(HeaderMapImplTest, SetReferenceKey) {
  HeaderMapImpl headers;
  LowerCaseString foo("STR");
  headers.setReferenceKey(foo, "STR");
  EXPECT_NE("STR", headers.get(foo)->value().getStringView().data());
  EXPECT_EQ("STR", headers.get(foo)->value().getStringView());

  headers.setReferenceKey(foo, "STR");
  EXPECT_NE("STR", headers.get(foo)->value().getStringView().data());
  EXPECT_EQ("STR", headers.get(foo)->value().getStringView());
}