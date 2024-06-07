IntegrationCodecClientPtr HttpIntegrationTest::makeHttpConnection(uint32_t port) {
  return makeHttpConnection(makeClientConnection(port));
}