TEST_P(TcpTunnelingIntegrationTest, UpstreamConnectingDownstreamDisconnect) {
  if (upstreamProtocol() == Http::CodecType::HTTP1) {
    return;
  }

#if defined(WIN32)
  
  
  
  
  
  return;
#endif

  config_helper_.addConfigModifier([&](envoy::config::bootstrap::v3::Bootstrap& bootstrap) -> void {
    envoy::extensions::filters::network::tcp_proxy::v3::TcpProxy proxy_config;
    proxy_config.set_stat_prefix("STR");
    proxy_config.set_cluster("STR");
    proxy_config.mutable_tunneling_config()->set_hostname("STR");

    
    
    proxy_config.mutable_max_connect_attempts()->set_value(2);

    auto* listeners = bootstrap.mutable_static_resources()->mutable_listeners();
    for (auto& listener : *listeners) {
      if (listener.name() != "STR") {
        continue;
      }
      auto* filter_chain = listener.mutable_filter_chains(0);
      auto* filter = filter_chain->mutable_filters(0);
      filter->mutable_typed_config()->PackFrom(proxy_config);

      
      
      envoy::extensions::transport_sockets::tls::v3::DownstreamTlsContext tls_context;
      ConfigHelper::initializeTls({}, *tls_context.mutable_common_tls_context());
      filter_chain->mutable_transport_socket()->set_name("STR");
      filter_chain->mutable_transport_socket()->mutable_typed_config()->PackFrom(tls_context);

      break;
    }
  });

  enableHalfClose(false);
  initialize();

  IntegrationTcpClientPtr tcp_client = makeTcpConnection(lookupPort("STR"));

  
  
  ASSERT_TRUE(fake_upstreams_[0]->waitForHttpConnection(*dispatcher_, fake_upstream_connection_));
  ASSERT_TRUE(fake_upstream_connection_->waitForNewStream(*dispatcher_, upstream_request_));
  ASSERT_TRUE(upstream_request_->waitForHeadersComplete());

  
  
  tcp_client->close();

  ASSERT_TRUE(upstream_request_->waitForReset());
  ASSERT_TRUE(fake_upstream_connection_->close());
}