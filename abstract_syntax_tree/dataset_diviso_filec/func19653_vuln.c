TEST_F(Http1ServerConnectionImplTest, ManyTrailersRejected) {
  
  testTrailersExceedLimit(createHeaderFragment(101), true);
}