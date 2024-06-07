TEST_F(HttpConnectionManagerImplTest, HeaderOnlyRequestAndResponseUsingHttp3) {
  setup(false, "STR", false);

  filter_callbacks_.connection_.stream_info_.protocol_ = Envoy::Http::Protocol::Http3;
  codec_->protocol_ = Http::Protocol::Http3;
  EXPECT_EQ(Network::FilterStatus::StopIteration, conn_manager_->onNewConnection());

  
  std::shared_ptr<MockStreamDecoderFilter> filter(new NiceMock<MockStreamDecoderFilter>());

  EXPECT_CALL(*filter, decodeHeaders(_, true))
      .WillOnce(Invoke([&](RequestHeaderMap& headers, bool) -> FilterHeadersStatus {
        EXPECT_NE(nullptr, headers.ForwardedFor());
        EXPECT_EQ("STR", headers.getForwardedProtoValue());
        return FilterHeadersStatus::StopIteration;
      }));

  EXPECT_CALL(*filter, setDecoderFilterCallbacks(_));

  EXPECT_CALL(filter_factory_, createFilterChain(_))
      .WillOnce(Invoke([&](FilterChainFactoryCallbacks& callbacks) -> void {
        callbacks.addStreamDecoderFilter(filter);
      }));

  EXPECT_CALL(filter_callbacks_.connection_.dispatcher_, deferredDelete_(_));

  
  
  NiceMock<MockResponseEncoder> encoder;
  RequestDecoder& decoder = conn_manager_->newStream(encoder);
  RequestHeaderMapPtr headers{
      new TestRequestHeaderMapImpl{{"STR"}}};
  decoder.decodeHeaders(std::move(headers), true);

  ResponseHeaderMapPtr response_headers{new TestResponseHeaderMapImpl{{"STR"}}};
  filter->callbacks_->encodeHeaders(std::move(response_headers), true);

  EXPECT_EQ(1U, stats_.named_.downstream_rq_2xx_.value());
  EXPECT_EQ(1U, listener_stats_.downstream_rq_2xx_.value());
  EXPECT_EQ(1U, stats_.named_.downstream_rq_completed_.value());
  EXPECT_EQ(1U, listener_stats_.downstream_rq_completed_.value());
  EXPECT_EQ(1U, stats_.named_.downstream_cx_http3_total_.value());
  filter_callbacks_.connection_.dispatcher_.clearDeferredDeleteList();
  conn_manager_.reset();
  EXPECT_EQ(0U, stats_.named_.downstream_cx_http3_active_.value());
}