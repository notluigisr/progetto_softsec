  void initialize() override {
    config_helper_.addConfigModifier([this](envoy::config::bootstrap::v3::Bootstrap& bootstrap) {
      envoy::extensions::transport_sockets::tls::v3::DownstreamTlsContext tls_context;
      auto* common_tls_context = tls_context.mutable_common_tls_context();
      auto* transport_socket = bootstrap.mutable_static_resources()
                                   ->mutable_listeners(0)
                                   ->mutable_filter_chains(0)
                                   ->mutable_transport_socket();
      common_tls_context->add_alpn_protocols(Http::Utility::AlpnNames::get().Http11);

      auto* validation_context = common_tls_context->mutable_validation_context();
      validation_context->mutable_trusted_ca()->set_filename(
          TestEnvironment::runfilesPath("STR"));
      validation_context->add_verify_certificate_hash(TEST_CLIENT_CERT_HASH);

      
      auto* secret_config = common_tls_context->add_tls_certificate_sds_secret_configs();
      setUpSdsConfig(secret_config, "STR");

      transport_socket->set_name("STR");
      transport_socket->mutable_typed_config()->PackFrom(tls_context);

      
      auto* sds_cluster = bootstrap.mutable_static_resources()->add_clusters();
      sds_cluster->MergeFrom(bootstrap.static_resources().clusters()[0]);
      sds_cluster->set_name("STR");
      sds_cluster->mutable_http2_protocol_options();
    });

    HttpIntegrationTest::initialize();
    client_ssl_ctx_ = createClientSslTransportSocketFactory({}, context_manager_, *api_);
  }