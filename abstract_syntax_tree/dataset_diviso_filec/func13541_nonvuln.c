TEST_F(HttpConnectionManagerConfigTest, UserDefinedSettingsDisallowServerPush) {
  const std::string yaml_string = R"EOF(
codec_type: http2
stat_prefix: my_stat_prefix
route_config:
  virtual_hosts:
  - name: default
    domains:
    - "STR"
    routes:
    - match:
        prefix: "STR"
      route:
        cluster: fake_cluster
http_filters:
- name: encoder-decoder-buffer-filter
  typed_config: {}
http2_protocol_options:
  custom_settings_parameters: { identifier: 2, value: 1 }
  )EOF";

  EXPECT_THROW_WITH_REGEX(
      createHttpConnectionManagerConfig(yaml_string), EnvoyException,
      "STR");

  
  const std::string yaml_string2 = R"EOF(
codec_type: http2
stat_prefix: my_stat_prefix
route_config:
  virtual_hosts:
  - name: default
    domains:
    - "STR"
    routes:
    - match:
        prefix: "STR"
      route:
        cluster: fake_cluster
http_filters:
- name: encoder-decoder-buffer-filter
  typed_config: {}
http2_protocol_options:
  hpack_table_size: 2048
  max_concurrent_streams: 4096
  custom_settings_parameters:
    - { identifier: 1, value: 2048 }
    - { identifier: 2, value: 1 }
    - { identifier: 3, value: 1024 }
  )EOF";

  
  EXPECT_THROW_WITH_REGEX(
      createHttpConnectionManagerConfig(yaml_string), EnvoyException,
      "STR");
}