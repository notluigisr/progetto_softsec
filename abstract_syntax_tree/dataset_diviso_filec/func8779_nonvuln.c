ConnectionImpl::ClientHttp2Options::ClientHttp2Options(
    const envoy::config::core::v3::Http2ProtocolOptions& http2_options)
    : Http2Options(http2_options) {
  
  
  
  
  nghttp2_option_set_peer_max_concurrent_streams(
      options_, ::Envoy::Http2::Utility::OptionsLimits::DEFAULT_MAX_CONCURRENT_STREAMS);
}