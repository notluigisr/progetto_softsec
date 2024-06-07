TEST_P(ProtocolIntegrationTest, Retry) {
  initialize();
  codec_client_ = makeHttpConnection(lookupPort("STR"));
  auto response =
      codec_client_->makeRequestWithBody(Http::TestHeaderMapImpl{{"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"}},
                                         1024);
  waitForNextUpstreamRequest();
  upstream_request_->encodeHeaders(Http::TestHeaderMapImpl{{"STR"}}, false);

  if (fake_upstreams_[0]->httpType() == FakeHttpConnection::Type::HTTP1) {
    ASSERT_TRUE(fake_upstream_connection_->waitForDisconnect());
    ASSERT_TRUE(fake_upstreams_[0]->waitForHttpConnection(*dispatcher_, fake_upstream_connection_));
  } else {
    ASSERT_TRUE(upstream_request_->waitForReset());
  }
  waitForNextUpstreamRequest();
  upstream_request_->encodeHeaders(default_response_headers_, false);
  upstream_request_->encodeData(512, true);

  response->waitForEndStream();
  EXPECT_TRUE(upstream_request_->complete());
  EXPECT_EQ(1024U, upstream_request_->bodyLength());

  EXPECT_TRUE(response->complete());
  EXPECT_EQ("STR", response->headers().Status()->value().getStringView());
  EXPECT_EQ(512U, response->body().size());
}