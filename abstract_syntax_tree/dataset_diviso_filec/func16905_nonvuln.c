TEST(HttpUtility, ValidateStreamErrors) {
  
  envoy::config::core::v3::Http2ProtocolOptions http2_options;
  EXPECT_FALSE(Envoy::Http2::Utility::initializeAndValidateOptions(http2_options)
                   .override_stream_error_on_invalid_http_message()
                   .value());

  
  http2_options.set_stream_error_on_invalid_http_messaging(true);
  EXPECT_TRUE(Envoy::Http2::Utility::initializeAndValidateOptions(http2_options)
                  .override_stream_error_on_invalid_http_message()
                  .value());

  
  http2_options.mutable_override_stream_error_on_invalid_http_message()->set_value(true);
  http2_options.set_stream_error_on_invalid_http_messaging(false);
  EXPECT_TRUE(Envoy::Http2::Utility::initializeAndValidateOptions(http2_options)
                  .override_stream_error_on_invalid_http_message()
                  .value());

  
  http2_options.mutable_override_stream_error_on_invalid_http_message()->set_value(false);
  http2_options.set_stream_error_on_invalid_http_messaging(true);
  EXPECT_FALSE(Envoy::Http2::Utility::initializeAndValidateOptions(http2_options)
                   .override_stream_error_on_invalid_http_message()
                   .value());
}