TEST_F(HttpConnectionManagerImplTest, TestAccessLogWithTrailers) {
  setup(false, "");

  std::shared_ptr<MockStreamDecoderFilter> filter(new NiceMock<MockStreamDecoderFilter>());
  std::shared_ptr<AccessLog::MockInstance> handler(new NiceMock<AccessLog::MockInstance>());

  EXPECT_CALL(filter_factory_, createFilterChain(_))
      .WillOnce(Invoke([&](FilterChainFactoryCallbacks& callbacks) -> void {
        callbacks.addStreamDecoderFilter(filter);
        callbacks.addAccessLogHandler(handler);
      }));

  EXPECT_CALL(*handler, log(_, _, _, _))
      .WillOnce(Invoke([](const HeaderMap*, const HeaderMap*, const HeaderMap*,
                          const StreamInfo::StreamInfo& stream_info) {
        EXPECT_TRUE(stream_info.responseCode());
        EXPECT_EQ(stream_info.responseCode().value(), uint32_t(200));
        EXPECT_NE(nullptr, stream_info.downstreamLocalAddress());
        EXPECT_NE(nullptr, stream_info.downstreamRemoteAddress());
        EXPECT_NE(nullptr, stream_info.downstreamDirectRemoteAddress());
        EXPECT_NE(nullptr, stream_info.routeEntry());
      }));

  NiceMock<MockResponseEncoder> encoder;
  EXPECT_CALL(*codec_, dispatch(_))
      .WillRepeatedly(Invoke([&](Buffer::Instance& data) -> Http::Status {
        RequestDecoder* decoder = &conn_manager_->newStream(encoder);

        RequestHeaderMapPtr headers{
            new TestRequestHeaderMapImpl{{"STR"},
                                         {"STR"},
                                         {"STR"},
                                         {"STR"}}};
        decoder->decodeHeaders(std::move(headers), true);

        ResponseHeaderMapPtr response_headers{new TestResponseHeaderMapImpl{{"STR"}}};
        filter->callbacks_->encodeHeaders(std::move(response_headers), false);

        ResponseTrailerMapPtr response_trailers{new TestResponseTrailerMapImpl{{"STR"}}};
        filter->callbacks_->encodeTrailers(std::move(response_trailers));

        data.drain(4);
        return Http::okStatus();
      }));

  Buffer::OwnedImpl fake_input("STR");
  conn_manager_->onData(fake_input, false);
}