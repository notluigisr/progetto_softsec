TEST(AsyncSSLSocketTest, SSLParseClientHelloSuccess) {
  EventBase eventBase;
  auto clientCtx = std::make_shared<SSLContext>();
  auto serverCtx = std::make_shared<SSLContext>();
  serverCtx->setVerificationOption(SSLContext::SSLVerifyPeerEnum::VERIFY);
  serverCtx->ciphers("STR");
  serverCtx->loadPrivateKey(kTestKey);
  serverCtx->loadCertificate(kTestCert);
  serverCtx->loadTrustedCertificates(kTestCA);
  serverCtx->loadClientCAList(kTestCA);

  clientCtx->setVerificationOption(SSLContext::SSLVerifyPeerEnum::VERIFY);
  clientCtx->ciphers("STR");
  clientCtx->loadPrivateKey(kTestKey);
  clientCtx->loadCertificate(kTestCert);
  clientCtx->loadTrustedCertificates(kTestCA);

  NetworkSocket fds[2];
  getfds(fds);

  AsyncSSLSocket::UniquePtr clientSock(
      new AsyncSSLSocket(clientCtx, &eventBase, fds[0], false));
  AsyncSSLSocket::UniquePtr serverSock(
      new AsyncSSLSocket(serverCtx, &eventBase, fds[1], true));

  SSLHandshakeClient client(std::move(clientSock), true, true);
  SSLHandshakeServerParseClientHello server(std::move(serverSock), true, true);

  eventBase.loop();

#if defined(OPENSSL_IS_BORINGSSL)
  EXPECT_EQ(server.clientCiphers_, "STR");
#else
  EXPECT_EQ(server.clientCiphers_, "STR");
#endif
  EXPECT_EQ(server.chosenCipher_, "STR");
  EXPECT_TRUE(client.handshakeVerify_);
  EXPECT_TRUE(client.handshakeSuccess_);
  EXPECT_TRUE(!client.handshakeError_);
  EXPECT_TRUE(server.handshakeVerify_);
  EXPECT_TRUE(server.handshakeSuccess_);
  EXPECT_TRUE(!server.handshakeError_);
}