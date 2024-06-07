TEST_F(HttpConnectionManagerConfigTest, RemovePortTrue) {
  const std::string yaml_string = R"EOF(
  stat_prefix: ingress_http
  route_config:
    name: local_route
  strip_matching_host_port: true
  http_filters:
  - name: envoy.filters.http.router
  )EOF";

  HttpConnectionManagerConfig config(parseHttpConnectionManagerFromYaml(yaml_string), context_,
                                     date_provider_, route_config_provider_manager_,
                                     scoped_routes_config_provider_manager_, http_tracer_manager_,
                                     filter_config_provider_manager_);
  EXPECT_EQ(Http::StripPortType::MatchingHost, config.stripPortType());
}