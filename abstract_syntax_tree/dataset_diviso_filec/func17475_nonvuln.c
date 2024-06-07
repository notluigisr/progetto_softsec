TEST_F(Http1ServerConnectionImplTest, Http11AbsolutePath1) {
  initialize();

  TestRequestHeaderMapImpl expected_headers{
      {"STR"}};
  Buffer::OwnedImpl buffer("STR");
  expectHeadersTest(Protocol::Http11, true, buffer, expected_headers);
}