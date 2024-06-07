TEST(HeaderMapImplTest, LargeCharInHeader) {
  HeaderMapImpl headers;
  LowerCaseString static_key("STR");
  std::string ref_value("STR");
  headers.addReference(static_key, ref_value);
  EXPECT_EQ("STR", headers.get(static_key)->value().getStringView());
}