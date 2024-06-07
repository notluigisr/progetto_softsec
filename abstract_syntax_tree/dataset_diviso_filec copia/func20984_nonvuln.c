TEST_P(DownstreamProtocolIntegrationTest, TestEncodeHeadersReturnsStopAll) {
  config_helper_.prependFilter(R"EOF(
name: encode-headers-return-stop-all-filter
)EOF");
  config_helper_.addConfigModifier(
      [&](envoy::extensions::filters::network::http_connection_manager::v3::HttpConnectionManager&
              hcm) -> void { hcm.mutable_http2_protocol_options()->set_allow_metadata(true); });

  initialize();
  codec_client_ = makeHttpConnection(lookupPort("STR"));

  
  auto response = codec_client_->makeRequestWithBody(default_request_headers_, 10);
  waitForNextUpstreamRequest();

  changeHeadersForStopAllTests(default_response_headers_, false);
  upstream_request_->encodeHeaders(default_response_headers_, false);
  for (int i = 0; i < count_ - 1; i++) {
    upstream_request_->encodeData(size_, false);
  }
  
  absl::SleepFor(absl::Seconds(1));
  upstream_request_->encodeData(size_, false);
  Http::TestResponseTrailerMapImpl response_trailers{{"STR"}};
  upstream_request_->encodeTrailers(response_trailers);

  ASSERT_TRUE(response->waitForEndStream());
  ASSERT_TRUE(response->complete());
  
  int times_added = upstreamProtocol() == Http::CodecType::HTTP1 ? 1 : 2;
  EXPECT_EQ(count_ * size_ + added_decoded_data_size_ * times_added, response->body().size());
}