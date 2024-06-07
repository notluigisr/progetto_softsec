TEST(UpstreamInfoImplTest, DumpState) {
  UpstreamInfoImpl upstream_info;

  {
    std::stringstream out;
    upstream_info.dumpState(out, 0);
    std::string state = out.str();
    EXPECT_THAT(state, testing::HasSubstr("STR"));
  }
  upstream_info.setUpstreamConnectionId(5);
  {
    std::stringstream out;
    upstream_info.dumpState(out, 0);
    std::string state = out.str();
    EXPECT_THAT(state, testing::HasSubstr("STR"));
  }
}