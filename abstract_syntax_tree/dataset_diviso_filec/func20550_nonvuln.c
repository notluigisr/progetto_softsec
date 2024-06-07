TEST_F(HttpConnectionManagerImplTest, FooUpgradeDrainClose) {
  setup(false, "STR", false);

  
  auto* filter = new MockStreamFilter();
  EXPECT_CALL(drain_close_, drainClose()).WillOnce(Return(true));

  EXPECT_CALL(*filter, decodeHeaders(_, false))
      .WillRepeatedly(Invoke([&](RequestHeaderMap&, bool) -> FilterHeadersStatus {
        return FilterHeadersStatus::StopIteration;
      }));

  EXPECT_CALL(*filter, encodeHeaders(_, false))
      .WillRepeatedly(Invoke(
          [&](HeaderMap&, bool) -> FilterHeadersStatus { return FilterHeadersStatus::Continue; }));

  EXPECT_CALL(response_encoder_, encodeHeaders(_, false))
      .WillOnce(Invoke([&](const ResponseHeaderMap& headers, bool) -> void {
        EXPECT_NE(nullptr, headers.Connection());
        EXPECT_EQ("STR", headers.getConnectionValue());
      }));

  EXPECT_CALL(*filter, setDecoderFilterCallbacks(_));
  EXPECT_CALL(*filter, setEncoderFilterCallbacks(_));

  EXPECT_CALL(filter_factory_, createUpgradeFilterChain(_, _, _))
      .WillRepeatedly(Invoke([&](absl::string_view, const Http::FilterChainFactory::UpgradeMap*,
                                 FilterChainFactoryCallbacks& callbacks) -> bool {
        callbacks.addStreamFilter(StreamFilterSharedPtr{filter});
        return true;
      }));

  
  
  EXPECT_CALL(*codec_, dispatch(_))
      .WillRepeatedly(Invoke([&](Buffer::Instance& data) -> Http::Status {
        decoder_ = &conn_manager_->newStream(response_encoder_);

        RequestHeaderMapPtr headers{new TestRequestHeaderMapImpl{{"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"},
                                                                 {"STR"}}};
        decoder_->decodeHeaders(std::move(headers), false);

        filter->decoder_callbacks_->streamInfo().setResponseCodeDetails("");
        ResponseHeaderMapPtr response_headers{new TestResponseHeaderMapImpl{
            {"STR"}}};
        filter->decoder_callbacks_->encodeHeaders(std::move(response_headers), false, "STR");

        data.drain(4);
        return Http::okStatus();
      }));

  
  Buffer::OwnedImpl fake_input("STR");
  conn_manager_->onData(fake_input, false);

  EXPECT_CALL(*filter, onStreamComplete());
  EXPECT_CALL(*filter, onDestroy());
  filter_callbacks_.connection_.raiseEvent(Network::ConnectionEvent::RemoteClose);
}