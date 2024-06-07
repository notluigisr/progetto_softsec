  void initialize() override {
    allow_metadata_ = true;
    http2OptionsFromTuple(client_http2_options_, client_settings_);
    http2OptionsFromTuple(server_http2_options_, server_settings_);
    client_ = std::make_unique<MetadataTestClientConnectionImpl>(
        client_connection_, client_callbacks_, stats_store_, client_http2_options_,
        max_request_headers_kb_, max_response_headers_count_, http2_session_factory_);
    server_ = std::make_unique<TestServerConnectionImpl>(
        server_connection_, server_callbacks_, stats_store_, server_http2_options_,
        max_request_headers_kb_, max_request_headers_count_, headers_with_underscores_action_);
    ON_CALL(client_connection_, write(_, _))
        .WillByDefault(Invoke([&](Buffer::Instance& data, bool) -> void {
          ASSERT_TRUE(server_wrapper_.dispatch(data, *server_).ok());
        }));
    ON_CALL(server_connection_, write(_, _))
        .WillByDefault(Invoke([&](Buffer::Instance& data, bool) -> void {
          ASSERT_TRUE(client_wrapper_.dispatch(data, *client_).ok());
        }));
  }