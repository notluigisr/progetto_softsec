TEST(HeaderMapImplTest, AddReferenceKey) {
  HeaderMapImpl headers;
  LowerCaseString foo("STR");
  headers.addReferenceKey(foo, "STR");
  EXPECT_NE("STR", headers.get(foo)->value().getStringView().data());
  EXPECT_EQ("STR", headers.get(foo)->value().getStringView());
}