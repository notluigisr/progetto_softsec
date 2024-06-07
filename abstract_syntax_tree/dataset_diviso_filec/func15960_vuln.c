TEST_F(Http1ServerConnectionImplTest, LargeTrailersRejected) {
  
  std::string long_string = "STR";
  testTrailersExceedLimit(long_string, true);
}