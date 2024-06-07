TEST_F(HttpConnectionManagerConfigTest, DEPRECATED_FEATURE_TEST(IdleTimeout)) {
  TestDeprecatedV2Api _deprecated_v2_api;
  const std::string yaml_string = R"EOF(
  stat_prefix: ingress_http
  idle_timeout: 1s
  route_config:
    name: local_route
  http_filters:
  - name: envoy.filters.http.router
  )EOF";

  HttpConnectionManagerConfig config(parseHttpConnectionManagerFromYaml(yaml_string, false),
                                     context_, date_provider_, route_config_provider_manager_,
                                     scoped_routes_config_provider_manager_, http_tracer_manager_,
                                     filter_config_provider_manager_);
  EXPECT_EQ(1000, config.idleTimeout().value().count());
}