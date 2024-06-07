TEST_F(HttpConnectionManagerImplTest, UnderlyingConnectionWatermarksUnwoundWithLazyCreation) {
  setup(false, "");

  
  EXPECT_CALL(*codec_, dispatch(_));
  Buffer::OwnedImpl fake_input("");
  conn_manager_->onData(fake_input, false);

  
  ASSERT_EQ(decoder_filters_.size(), 0);
  EXPECT_CALL(*codec_, onUnderlyingConnectionAboveWriteBufferHighWatermark());
  conn_manager_->onAboveWriteBufferHighWatermark();

  
  
  StreamDecoder* decoder;
  {
    setUpBufferLimits();
    EXPECT_CALL(*codec_, dispatch(_)).WillOnce(Invoke([&](Buffer::Instance&) -> void {
      decoder = &conn_manager_->newStream(response_encoder_);
      
      stream_callbacks_->onAboveWriteBufferHighWatermark();
    }));

    
    Buffer::OwnedImpl fake_input2("STR");
    conn_manager_->onData(fake_input2, false);
  }

  
  
  ASSERT(stream_callbacks_ != nullptr);
  EXPECT_CALL(*codec_, onUnderlyingConnectionBelowWriteBufferLowWatermark())
      .WillOnce(Invoke([&]() -> void { stream_callbacks_->onBelowWriteBufferLowWatermark(); }));
  conn_manager_->onBelowWriteBufferLowWatermark();

  
  
  {
    setupFilterChain(2, 2);
    EXPECT_CALL(filter_callbacks_.connection_, aboveHighWatermark()).Times(0);
    EXPECT_CALL(*codec_, dispatch(_)).WillOnce(Invoke([&](Buffer::Instance&) -> void {
      HeaderMapPtr headers{
          new TestHeaderMapImpl{{"STR"}}};
      decoder->decodeHeaders(std::move(headers), true);
    }));
    EXPECT_CALL(*decoder_filters_[0], decodeHeaders(_, true))
        .WillOnce(InvokeWithoutArgs([&]() -> FilterHeadersStatus {
          Buffer::OwnedImpl data("STR");
          decoder_filters_[0]->callbacks_->addDecodedData(data, true);
          return FilterHeadersStatus::Continue;
        }));
    EXPECT_CALL(*decoder_filters_[0], decodeComplete());
    sendRequestHeadersAndData();
    ASSERT_GE(decoder_filters_.size(), 1);
    MockDownstreamWatermarkCallbacks callbacks;
    EXPECT_CALL(callbacks, onAboveWriteBufferHighWatermark()).Times(0);
    EXPECT_CALL(callbacks, onBelowWriteBufferLowWatermark()).Times(0);
    decoder_filters_[0]->callbacks_->addDownstreamWatermarkCallbacks(callbacks);
  }
}