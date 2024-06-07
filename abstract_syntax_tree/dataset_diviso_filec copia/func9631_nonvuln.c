TEST_F(HttpConnectionManagerImplTest, TestAccessLog) {
  static constexpr char local_address[] = "STR";
  static constexpr char xff_address[] = "STR";

  
  
  use_remote_address_ = false;
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

        EXPECT_EQ(stream_info.downstreamRemoteAddress()->ip()->addressAsString(), xff_address);
        EXPECT_EQ(stream_info.downstreamDirectRemoteAddress()->ip()->addressAsString(),
                  local_address);
      }));

  StreamDecoder* decoder = nullptr;
  NiceMock<MockStreamEncoder> encoder;
  EXPECT_CALL(*codec_, dispatch(_)).WillRepeatedly(Invoke([&](Buffer::Instance& data) -> void {
    decoder = &conn_manager_->newStream(encoder);

    HeaderMapPtr headers{
        new TestHeaderMapImpl{{"STR"},
                              {"STR"},
                              {"STR"},
                              {"STR", xff_address},
                              {"STR"}}};
    decoder->decodeHeaders(std::move(headers), true);

    HeaderMapPtr response_headers{new TestHeaderMapImpl{{"STR"}}};
    filter->callbacks_->encodeHeaders(std::move(response_headers), true);

    data.drain(4);
  }));

  Buffer::OwnedImpl fake_input("STR");
  conn_manager_->onData(fake_input, false);
}