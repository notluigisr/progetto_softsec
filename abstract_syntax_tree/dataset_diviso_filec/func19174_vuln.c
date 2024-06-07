TEST_F(Http1ServerConnectionImplTest, LargeTrailersRejectedIgnored) {
  
  std::string long_string = "STR";
  testTrailersExceedLimit(long_string, false);
}