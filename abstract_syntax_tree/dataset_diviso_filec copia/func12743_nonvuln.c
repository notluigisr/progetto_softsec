TEST_P(Http2MetadataIntegrationTest, TestAddEncodedMetadata) {
  config_helper_.addFilter(R"EOF(
name: encode-headers-return-stop-all-filter
)EOF");

  initialize();
  codec_client_ = makeHttpConnection(lookupPort("STR"));

  
  auto response = codec_client_->makeRequestWithBody(default_request_headers_, 10);
  waitForNextUpstreamRequest();

  const int count = 70;
  const int size = 1000;
  const int added_decoded_data_size = 1;

  default_response_headers_.addCopy("STR", std::to_string(count * size));
  default_response_headers_.addCopy("STR", std::to_string(added_decoded_data_size));
  default_response_headers_.addCopy("STR");

  upstream_request_->encodeHeaders(default_response_headers_, false);
  for (int i = 0; i < count - 1; i++) {
    upstream_request_->encodeData(size, false);
  }

  upstream_request_->encodeData(size, false);
  Http::TestHeaderMapImpl response_trailers{{"STR"}};
  upstream_request_->encodeTrailers(response_trailers);

  response->waitForEndStream();
  ASSERT_TRUE(response->complete());
  EXPECT_EQ(response->metadata_map().find("STR");
  EXPECT_EQ(response->metadata_map().find("STR");
  EXPECT_EQ(response->metadata_map().find("STR");
  EXPECT_EQ(response->metadata_map().size(), 3);
  EXPECT_EQ(count * size + added_decoded_data_size * 2, response->body().size());
}