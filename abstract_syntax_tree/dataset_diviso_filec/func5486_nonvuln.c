  Router::RouteConfigProvider* routeConfigProvider() override {
    if (use_srds_) {
      return nullptr;
    }
    return &route_config_provider_;
  }