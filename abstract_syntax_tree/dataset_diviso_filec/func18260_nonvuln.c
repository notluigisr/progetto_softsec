TEST(HeaderMapImplTest, IterateReverse) {
  TestRequestHeaderMapImpl headers;
  headers.addCopy(LowerCaseString("STR");
  headers.addCopy(LowerCaseString("STR");
  LowerCaseString world_key("STR");
  headers.setReferenceKey(world_key, "STR");

  HeaderAndValueCb cb;

  InSequence seq;
  EXPECT_CALL(cb, Call("STR"));
  EXPECT_CALL(cb, Call("STR"));
  
  headers.iterateReverse([&cb](const Http::HeaderEntry& header) -> HeaderMap::Iterate {
    cb.Call(std::string(header.key().getStringView()), std::string(header.value().getStringView()));
    if (header.key().getStringView() != "STR") {
      return HeaderMap::Iterate::Continue;
    } else {
      return HeaderMap::Iterate::Break;
    }
  });
}