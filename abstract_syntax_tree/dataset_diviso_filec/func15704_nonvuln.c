TEST_F(HttpConnectionManagerConfigTest, AlwaysSetRequestIdInResponseConfigured) {
  const std::string yaml_string = R"EOF(
  stat_prefix: ingress_http
  always_set_request_id_in_response: true
  route_config:
    name: local_route
  http_filters:
  - name: envoy.filters.http.router
  )EOF";

  HttpConnectionManagerConfig config(parseHttpConnectionManagerFromYaml(yaml_string), context_,
                                     date_provider_, route_config_provider_manager_,
                                     scoped_routes_config_provider_manager_, http_tracer_manager_,
                                     filter_config_provider_manager_);
  EXPECT_TRUE(config.alwaysSetRequestIdInResponse());
}