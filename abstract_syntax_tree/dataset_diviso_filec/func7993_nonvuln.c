  SslCertficateIntegrationTest() : SslIntegrationTestBase(std::get<0>(GetParam())) {
    server_tlsv1_3_ = true;
  }