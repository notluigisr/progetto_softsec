TEST(HeaderMapImplTest, SetCopy) {
  TestRequestHeaderMapImpl headers;
  LowerCaseString foo("STR");
  headers.setCopy(foo, "STR");
  EXPECT_EQ("STR", headers.get(foo)->value().getStringView());

  
  headers.setCopy(foo, "STR");
  EXPECT_EQ("STR", headers.get(foo)->value().getStringView());

  
  headers.addCopy(foo, "STR");
  EXPECT_EQ(headers.size(), 2);

  
  headers.setCopy(foo, "STR");
  EXPECT_EQ(headers.size(), 2);

  HeaderAndValueCb cb;

  InSequence seq;
  EXPECT_CALL(cb, Call("STR"));
  EXPECT_CALL(cb, Call("STR"));
  headers.iterate(cb.asIterateCb());

  
  EXPECT_EQ(2UL, headers.remove(foo));
  EXPECT_EQ(headers.size(), 0);
  const std::string empty;
  headers.setCopy(foo, empty);
  EXPECT_EQ(headers.size(), 1);
  headers.setCopy(foo, "STR");
  EXPECT_EQ(headers.get(foo)->value().getStringView(), "STR");

  
  headers.clear();
  EXPECT_EQ(headers.size(), 0);
  headers.setCopy(Headers::get().Path, "STR");
  EXPECT_EQ(headers.size(), 1);
  EXPECT_EQ(headers.getPathValue(), "STR");
  headers.setPath("STR");
  EXPECT_EQ(headers.size(), 1);
  EXPECT_EQ(headers.getPathValue(), "STR");
}