  void initialize() override {
    
    config_helper_.addConfigModifier([this](envoy::config::bootstrap::v3::Bootstrap& bootstrap) {
      
      if (upstream_tap_) {
        setupUpstreamTap(bootstrap);
      } else {
        setupDownstreamTap(bootstrap);
      }
    });
    SslIntegrationTest::initialize();
    
    debug_with_s_client_ = false;
  }