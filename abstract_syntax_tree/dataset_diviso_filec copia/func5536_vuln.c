  void initializeFilter(HeaderMode mode, bool inject_route_config_headers) {
    config_helper_.addConfigModifier(
        [&](envoy::extensions::filters::network::http_connection_manager::v3::HttpConnectionManager&
                hcm) {
          
          TestUtility::loadFromYaml(http_connection_mgr_config, hcm);
          envoy::extensions::filters::http::router::v3::Router router_config;
          router_config.set_suppress_envoy_headers(routerSuppressEnvoyHeaders());
          hcm.mutable_http_filters(0)->mutable_typed_config()->PackFrom(router_config);

          const bool append = mode == HeaderMode::Append;

          auto* route_config = hcm.mutable_route_config();
          if (inject_route_config_headers) {
            
            addHeader(route_config->mutable_response_headers_to_add(), "STR",
                      "STR", append);
            route_config->add_response_headers_to_remove("STR");
            addHeader(route_config->mutable_request_headers_to_add(), "STR",
                      "STR", append);
            route_config->add_request_headers_to_remove("STR");
          }

          if (use_eds_) {
            addHeader(route_config->mutable_response_headers_to_add(), "STR",
                      R"STR", append);

            
            
            for (auto& vhost : *route_config->mutable_virtual_hosts()) {
              addHeader(vhost.mutable_response_headers_to_add(), "STR",
                        R"STR", append);

              for (auto& route : *vhost.mutable_routes()) {
                addHeader(route.mutable_response_headers_to_add(), "STR",
                          R"STR", append);

                if (route.has_route()) {
                  auto* route_action = route.mutable_route();
                  if (route_action->has_weighted_clusters()) {
                    for (auto& c : *route_action->mutable_weighted_clusters()->mutable_clusters()) {
                      addHeader(c.mutable_response_headers_to_add(), "STR",
                                R"STR",
                                append);
                    }
                  }
                }
              }
            }
          }

          hcm.mutable_normalize_path()->set_value(normalize_path_);

          if (append) {
            
            return;
          }

          
          for (auto& vhost : *route_config->mutable_virtual_hosts()) {
            disableHeaderValueOptionAppend(*vhost.mutable_request_headers_to_add());
            disableHeaderValueOptionAppend(*vhost.mutable_response_headers_to_add());

            for (auto& route : *vhost.mutable_routes()) {
              disableHeaderValueOptionAppend(*route.mutable_request_headers_to_add());
              disableHeaderValueOptionAppend(*route.mutable_response_headers_to_add());

              if (route.has_route()) {
                auto* route_action = route.mutable_route();

                if (route_action->has_weighted_clusters()) {
                  for (auto& c : *route_action->mutable_weighted_clusters()->mutable_clusters()) {
                    disableHeaderValueOptionAppend(*c.mutable_request_headers_to_add());
                    disableHeaderValueOptionAppend(*c.mutable_response_headers_to_add());
                  }
                }
              }
            }
          }
        });

    initialize();
  }