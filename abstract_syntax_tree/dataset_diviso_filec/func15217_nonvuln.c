void Http2UpstreamIntegrationTest::simultaneousRequest(uint32_t request1_bytes,
                                                       uint32_t request2_bytes,
                                                       uint32_t response1_bytes,
                                                       uint32_t response2_bytes) {
  FakeStreamPtr upstream_request1;
  FakeStreamPtr upstream_request2;
  initialize();
  codec_client_ = makeHttpConnection(lookupPort("STR"));

  
  auto encoder_decoder1 =
      codec_client_->startRequest(Http::TestRequestHeaderMapImpl{{"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"}});
  Http::RequestEncoder* encoder1 = &encoder_decoder1.first;
  auto response1 = std::move(encoder_decoder1.second);
  ASSERT_TRUE(fake_upstreams_[0]->waitForHttpConnection(*dispatcher_, fake_upstream_connection_));
  ASSERT_TRUE(fake_upstream_connection_->waitForNewStream(*dispatcher_, upstream_request1));

  
  auto encoder_decoder2 =
      codec_client_->startRequest(Http::TestRequestHeaderMapImpl{{"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"}});
  Http::RequestEncoder* encoder2 = &encoder_decoder2.first;
  auto response2 = std::move(encoder_decoder2.second);
  ASSERT_TRUE(fake_upstream_connection_->waitForNewStream(*dispatcher_, upstream_request2));

  
  codec_client_->sendData(*encoder1, request1_bytes, true);
  ASSERT_TRUE(upstream_request1->waitForEndStream(*dispatcher_));

  
  codec_client_->sendData(*encoder2, request2_bytes, true);
  ASSERT_TRUE(upstream_request2->waitForEndStream(*dispatcher_));

  
  upstream_request2->encodeHeaders(Http::TestResponseHeaderMapImpl{{"STR"}}, false);
  upstream_request2->encodeData(response2_bytes, true);
  response2->waitForEndStream();
  EXPECT_TRUE(upstream_request2->complete());
  EXPECT_EQ(request2_bytes, upstream_request2->bodyLength());
  EXPECT_TRUE(response2->complete());
  EXPECT_EQ("STR", response2->headers().getStatusValue());
  EXPECT_EQ(response2_bytes, response2->body().size());

  
  upstream_request1->encodeHeaders(Http::TestResponseHeaderMapImpl{{"STR"}}, false);
  upstream_request1->encodeData(response1_bytes, true);
  response1->waitForEndStream();
  EXPECT_TRUE(upstream_request1->complete());
  EXPECT_EQ(request1_bytes, upstream_request1->bodyLength());
  EXPECT_TRUE(response1->complete());
  EXPECT_EQ("STR", response1->headers().getStatusValue());
  EXPECT_EQ(response1_bytes, response1->body().size());
}