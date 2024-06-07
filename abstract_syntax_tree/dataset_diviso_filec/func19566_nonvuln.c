TEST_F(HttpConnectionManagerImplTest, InvalidPathWithDualFilter) {
  InSequence s;
  setup(false, "");

  EXPECT_CALL(*codec_, dispatch(_)).WillOnce(Invoke([&](Buffer::Instance& data) -> Http::Status {
    decoder_ = &conn_manager_->newStream(response_encoder_);
    RequestHeaderMapPtr headers{new TestRequestHeaderMapImpl{
        {"STR"}}};
    decoder_->decodeHeaders(std::move(headers), true);
    data.drain(4);
    return Http::okStatus();
  }));

  
  auto* filter = new MockStreamFilter();
  EXPECT_CALL(filter_factory_, createFilterChain(_))
      .WillOnce(Invoke([&](FilterChainFactoryCallbacks& callbacks) -> void {
        callbacks.addStreamFilter(StreamFilterSharedPtr{filter});
      }));
  EXPECT_CALL(*filter, setDecoderFilterCallbacks(_));
  EXPECT_CALL(*filter, setEncoderFilterCallbacks(_));

  EXPECT_CALL(*filter, encodeHeaders(_, true));
  EXPECT_CALL(*filter, encodeComplete());
  EXPECT_CALL(response_encoder_, encodeHeaders(_, true))
      .WillOnce(Invoke([&](const ResponseHeaderMap& headers, bool) -> void {
        EXPECT_EQ("STR", headers.getStatusValue());
        EXPECT_EQ("STR",
                  filter->decoder_callbacks_->streamInfo().responseCodeDetails().value());
      }));
  EXPECT_CALL(*filter, onStreamComplete());
  EXPECT_CALL(*filter, onDestroy());

  Buffer::OwnedImpl fake_input("STR");
  conn_manager_->onData(fake_input, false);
}