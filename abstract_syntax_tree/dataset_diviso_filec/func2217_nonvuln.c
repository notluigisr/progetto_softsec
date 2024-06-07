TEST_P(ProxyProtocolTest, AddressVersionsNotMatch) {
  connect(false);
  write("STR");
  expectProxyProtoError();
}