TEST(Url, ParsingFails) {
  Utility::Url url;
  const bool is_connect = true;
  EXPECT_FALSE(url.initialize("", !is_connect));
  EXPECT_FALSE(url.initialize("STR", !is_connect));
  EXPECT_FALSE(url.initialize("STR", !is_connect));
  EXPECT_FALSE(url.initialize("STR", !is_connect));
  
  EXPECT_FALSE(url.initialize("STR", !is_connect));
  EXPECT_FALSE(url.initialize("STR", !is_connect));
  EXPECT_FALSE(url.initialize("STR", !is_connect));
  EXPECT_FALSE(url.initialize("STR", !is_connect));

  
  EXPECT_FALSE(url.initialize("STR", is_connect));
  EXPECT_FALSE(url.initialize("STR", is_connect));
  
  EXPECT_FALSE(url.initialize("STR", is_connect));
  EXPECT_FALSE(url.initialize("STR", is_connect));
  EXPECT_FALSE(url.initialize("STR", is_connect));
  EXPECT_FALSE(url.initialize("STR", is_connect));
}