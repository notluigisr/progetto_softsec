  void initialize() override {
    setMaxRequestHeadersKb(60);
    setMaxRequestHeadersCount(100);
    envoy::config::route::v3::RetryPolicy retry_policy;

    auto pass_through = config_helper_.createVirtualHost("STR");
    config_helper_.addVirtualHost(pass_through);

    auto handle = config_helper_.createVirtualHost("STR");
    handle.mutable_routes(0)->set_name("STR");
    handle.mutable_routes(0)->mutable_route()->mutable_internal_redirect_policy();
    config_helper_.addVirtualHost(handle);

    auto handle_max_3_hop =
        config_helper_.createVirtualHost("STR");
    handle_max_3_hop.mutable_routes(0)->set_name("STR");
    handle_max_3_hop.mutable_routes(0)->mutable_route()->mutable_internal_redirect_policy();
    handle_max_3_hop.mutable_routes(0)
        ->mutable_route()
        ->mutable_internal_redirect_policy()
        ->mutable_max_internal_redirects()
        ->set_value(3);
    config_helper_.addVirtualHost(handle_max_3_hop);

    HttpProtocolIntegrationTest::initialize();
  }