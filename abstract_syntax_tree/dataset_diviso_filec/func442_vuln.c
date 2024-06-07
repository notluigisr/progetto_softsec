TEST(HeaderMapImplTest, SetRemovesAllValues) {
  HeaderMapImpl headers;

  LowerCaseString key1("STR");
  LowerCaseString key2("STR");
  std::string ref_value1("STR");
  std::string ref_value2("STR");
  std::string ref_value3("STR");
  std::string ref_value4("STR");
  std::string ref_value5("STR");

  headers.addReference(key1, ref_value1);
  headers.addReference(key2, ref_value2);
  headers.addReference(key1, ref_value3);
  headers.addReference(key1, ref_value4);

  using MockCb = testing::MockFunction<void(const std::string&, const std::string&)>;

  {
    MockCb cb;

    InSequence seq;
    EXPECT_CALL(cb, Call("STR"));
    EXPECT_CALL(cb, Call("STR"));
    EXPECT_CALL(cb, Call("STR"));
    EXPECT_CALL(cb, Call("STR"));

    headers.iterate(
        [](const Http::HeaderEntry& header, void* cb_v) -> HeaderMap::Iterate {
          static_cast<MockCb*>(cb_v)->Call(std::string(header.key().getStringView()),
                                           std::string(header.value().getStringView()));
          return HeaderMap::Iterate::Continue;
        },
        &cb);
  }

  headers.setReference(key1, ref_value5); 

  {
    MockCb cb;

    InSequence seq;
    EXPECT_CALL(cb, Call("STR"));
    EXPECT_CALL(cb, Call("STR"));

    headers.iterate(
        [](const Http::HeaderEntry& header, void* cb_v) -> HeaderMap::Iterate {
          static_cast<MockCb*>(cb_v)->Call(std::string(header.key().getStringView()),
                                           std::string(header.value().getStringView()));
          return HeaderMap::Iterate::Continue;
        },
        &cb);
  }
}