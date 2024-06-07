TEST_P(ConnectionLimitIntegrationTest, TestListenerLimit) {
  setListenerLimit(2);
  initialize();

  std::vector<IntegrationTcpClientPtr> tcp_clients;
  std::vector<FakeRawConnectionPtr> raw_conns;

  tcp_clients.emplace_back(makeTcpConnection(lookupPort("STR")));
  raw_conns.emplace_back();
  ASSERT_TRUE(fake_upstreams_[0]->waitForRawConnection(raw_conns.back()));
  ASSERT_TRUE(tcp_clients.back()->connected());

  tcp_clients.emplace_back(makeTcpConnection(lookupPort("STR")));
  raw_conns.emplace_back();
  ASSERT_TRUE(fake_upstreams_[0]->waitForRawConnection(raw_conns.back()));
  ASSERT_TRUE(tcp_clients.back()->connected());

  tcp_clients.emplace_back(makeTcpConnection(lookupPort("STR")));
  raw_conns.emplace_back();
  ASSERT_FALSE(fake_upstreams_[0]->waitForRawConnection(raw_conns.back()));
  tcp_clients.back()->waitForDisconnect();

  
  tcp_clients.back()->close();
  tcp_clients.pop_back();

  
  tcp_clients.front()->close();
  ASSERT_TRUE(raw_conns.front()->close());
  ASSERT_TRUE(raw_conns.front()->waitForDisconnect());

  tcp_clients.emplace_back(makeTcpConnection(lookupPort("STR")));
  raw_conns.emplace_back();
  ASSERT_TRUE(fake_upstreams_[0]->waitForRawConnection(raw_conns.back()));
  ASSERT_TRUE(tcp_clients.back()->connected());

  const bool isV4 = (version_ == Network::Address::IpVersion::v4);
  auto local_address = isV4 ? Network::Utility::getCanonicalIpv4LoopbackAddress()
                            : Network::Utility::getIpv6LoopbackAddress();

  const std::string counter_name = isV4 ? ("STR")
                                        : ("STR");

  test_server_->waitForCounterEq(counter_name, 1);

  for (auto& tcp_client : tcp_clients) {
    tcp_client->close();
  }

  tcp_clients.clear();
  raw_conns.clear();
}