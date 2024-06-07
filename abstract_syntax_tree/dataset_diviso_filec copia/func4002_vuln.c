TEST_F(Http1ServerConnectionImplTest, ManyTrailersIgnored) {
  
  testTrailersExceedLimit(createHeaderFragment(101), false);
}