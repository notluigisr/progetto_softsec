TEST_F(HttpConnectionManagerImplTest, PerStreamIdleTimeoutNotConfigured) {
  setup(false, "");

  EXPECT_CALL(filter_callbacks_.connection_.dispatcher_, createTimer_(_)).Times(0);
  EXPECT_CALL(*codec_, dispatch(_))
      .WillRepeatedly(Invoke([&](Buffer::Instance& data) -> Http::Status {
        RequestDecoder* decoder = &conn_manager_->newStream(response_encoder_);

        RequestHeaderMapPtr headers{new TestRequestHeaderMapImpl{
            {"STR"}}};
        decoder->decodeHeaders(std::move(headers), false);

        data.drain(4);
        return Http::okStatus();
      }));

  Buffer::OwnedImpl fake_input("STR");
  conn_manager_->onData(fake_input, false);

  EXPECT_EQ(0U, stats_.named_.downstream_rq_idle_timeout_.value());
}