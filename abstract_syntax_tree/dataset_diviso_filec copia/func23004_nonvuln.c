TEST_F(HttpConnectionManagerImplTest, PerStreamIdleTimeoutAfterBidiData) {
  setup(false, "");
  ON_CALL(route_config_provider_.route_config_->route_->route_entry_, idleTimeout())
      .WillByDefault(Return(std::chrono::milliseconds(10)));
  proxy_100_continue_ = true;

  
  std::shared_ptr<MockStreamDecoderFilter> filter(new NiceMock<MockStreamDecoderFilter>());

  EXPECT_CALL(filter_factory_, createFilterChain(_))
      .WillRepeatedly(Invoke([&](FilterChainFactoryCallbacks& callbacks) -> void {
        callbacks.addStreamDecoderFilter(filter);
      }));
  EXPECT_CALL(filter_callbacks_.connection_.dispatcher_, deferredDelete_(_));

  
  
  Event::MockTimer* idle_timer = setUpTimer();
  StreamDecoder* decoder;
  EXPECT_CALL(*codec_, dispatch(_)).WillOnce(Invoke([&](Buffer::Instance& data) -> void {
    decoder = &conn_manager_->newStream(response_encoder_);
    HeaderMapPtr headers{
        new TestHeaderMapImpl{{"STR"}}};
    EXPECT_CALL(*idle_timer, enableTimer(_, _));
    decoder->decodeHeaders(std::move(headers), false);

    HeaderMapPtr response_continue_headers{new TestHeaderMapImpl{{"STR"}}};
    EXPECT_CALL(*idle_timer, enableTimer(_, _));
    filter->callbacks_->encode100ContinueHeaders(std::move(response_continue_headers));

    HeaderMapPtr response_headers{new TestHeaderMapImpl{{"STR"}}};
    EXPECT_CALL(*idle_timer, enableTimer(_, _));
    filter->callbacks_->encodeHeaders(std::move(response_headers), false);

    EXPECT_CALL(*idle_timer, enableTimer(_, _));
    decoder->decodeData(data, false);

    HeaderMapPtr trailers{new TestHeaderMapImpl{{"STR"}}};
    EXPECT_CALL(*idle_timer, enableTimer(_, _));
    decoder->decodeTrailers(std::move(trailers));

    Buffer::OwnedImpl fake_response("STR");
    EXPECT_CALL(*idle_timer, enableTimer(_, _));
    filter->callbacks_->encodeData(fake_response, false);

    EXPECT_CALL(*idle_timer, disableTimer());
    idle_timer->invokeCallback();

    data.drain(4);
  }));

  
  EXPECT_CALL(response_encoder_, encode100ContinueHeaders(_));

  
  EXPECT_CALL(response_encoder_, encodeHeaders(_, false))
      .WillOnce(Invoke([](const HeaderMap& headers, bool) -> void {
        EXPECT_EQ("STR", headers.Status()->value().getStringView());
      }));

  std::string response_body;
  EXPECT_CALL(response_encoder_, encodeData(_, false)).WillOnce(AddBufferToString(&response_body));

  Buffer::OwnedImpl fake_input("STR");
  conn_manager_->onData(fake_input, false);

  EXPECT_EQ(1U, stats_.named_.downstream_rq_idle_timeout_.value());
  EXPECT_EQ("STR", response_body);
}