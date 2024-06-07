TEST_F(HttpConnectionManagerImplTest, RequestTimeoutIsDisarmedOnCompleteRequestWithHeader) {
  request_timeout_ = std::chrono::milliseconds(10);
  setup(false, "");

  EXPECT_CALL(*codec_, dispatch(_)).WillOnce(Invoke([&](Buffer::Instance&) -> Http::Status {
    Event::MockTimer* request_timer = setUpTimer();
    EXPECT_CALL(*request_timer, enableTimer(request_timeout_, _));

    decoder_ = &conn_manager_->newStream(response_encoder_);
    RequestHeaderMapPtr headers{
        new TestRequestHeaderMapImpl{{"STR"}}};

    EXPECT_CALL(*request_timer, disableTimer()).Times(2);
    decoder_->decodeHeaders(std::move(headers), true);
    return Http::okStatus();
  }));

  Buffer::OwnedImpl fake_input("STR");
  conn_manager_->onData(fake_input, false); 

  EXPECT_EQ(0U, stats_.named_.downstream_rq_timeout_.value());

  expectOnDestroy();
  filter_callbacks_.connection_.raiseEvent(Network::ConnectionEvent::RemoteClose);
}