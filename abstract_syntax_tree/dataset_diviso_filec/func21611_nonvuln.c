TEST_P(ProtocolIntegrationTest, AddEncodedTrailers) {
  config_helper_.addFilter(R"EOF(
name: add-trailers-filter
config: {}
)EOF");
  initialize();

  codec_client_ = makeHttpConnection(lookupPort("STR"));
  auto response = codec_client_->makeRequestWithBody(default_request_headers_, 128);
  waitForNextUpstreamRequest();
  upstream_request_->encodeHeaders(Http::TestHeaderMapImpl{{"STR"}}, false);
  upstream_request_->encodeData(128, true);
  response->waitForEndStream();

  if (upstreamProtocol() == FakeHttpConnection::Type::HTTP2) {
    EXPECT_EQ("STR", upstream_request_->trailers()->GrpcMessage()->value().getStringView());
  }
  EXPECT_TRUE(response->complete());
  EXPECT_EQ("STR", response->headers().Status()->value().getStringView());
  if (downstream_protocol_ == Http::CodecClient::Type::HTTP2) {
    EXPECT_EQ("STR", response->trailers()->GrpcMessage()->value().getStringView());
  }
}