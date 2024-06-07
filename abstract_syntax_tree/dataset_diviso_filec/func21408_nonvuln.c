ConnectionImpl::ConnectionImpl(Network::Connection& connection, CodecStats& stats,
                               http_parser_type type, uint32_t max_headers_kb,
                               const uint32_t max_headers_count,
                               HeaderKeyFormatterPtr&& header_key_formatter, bool enable_trailers)
    : connection_(connection), stats_(stats),
      header_key_formatter_(std::move(header_key_formatter)), processing_trailers_(false),
      handling_upgrade_(false), reset_stream_called_(false), deferred_end_stream_headers_(false),
      strict_header_validation_(
          Runtime::runtimeFeatureEnabled("STR")),
      connection_header_sanitization_(Runtime::runtimeFeatureEnabled(
          "STR")),
      enable_trailers_(enable_trailers),
      reject_unsupported_transfer_encodings_(Runtime::runtimeFeatureEnabled(
          "STR")),
      strict_1xx_and_204_headers_(Runtime::runtimeFeatureEnabled(
          "STR")),
      output_buffer_([&]() -> void { this->onBelowLowWatermark(); },
                     [&]() -> void { this->onAboveHighWatermark(); },
                     []() -> void {  }),
      max_headers_kb_(max_headers_kb), max_headers_count_(max_headers_count) {
  output_buffer_.setWatermarks(connection.bufferLimit());
  http_parser_init(&parser_, type);
  parser_.data = this;
}