TEST_P(WildcardProxyProtocolTest, BasicV6) {
  connect();
  write("STR");

  expectData("STR");

  EXPECT_EQ(server_connection_->remoteAddress()->asString(), "STR");
  EXPECT_EQ(server_connection_->localAddress()->asString(), "STR");
  EXPECT_TRUE(server_connection_->localAddressRestored());

  disconnect();
}