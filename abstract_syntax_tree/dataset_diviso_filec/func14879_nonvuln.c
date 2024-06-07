  void setUpEncoderAndDecoder(bool request_with_data_and_trailers, bool decode_headers_stop_all) {
    setUpBufferLimits();
    EXPECT_CALL(*codec_, dispatch(_))
        .WillOnce(Invoke([&, request_with_data_and_trailers](Buffer::Instance&) -> void {
          StreamDecoder* decoder = &conn_manager_->newStream(response_encoder_);
          HeaderMapPtr headers{
              new TestHeaderMapImpl{{"STR"}}};
          if (request_with_data_and_trailers) {
            decoder->decodeHeaders(std::move(headers), false);

            Buffer::OwnedImpl fake_data("STR");
            decoder->decodeData(fake_data, false);

            HeaderMapPtr trailers{new TestHeaderMapImpl{{"STR"}}};
            decoder->decodeTrailers(std::move(trailers));
          } else {
            decoder->decodeHeaders(std::move(headers), true);
          }
        }));

    setupFilterChain(2, 2);

    EXPECT_CALL(*decoder_filters_[0], decodeHeaders(_, _))
        .WillOnce(InvokeWithoutArgs([&, decode_headers_stop_all]() -> FilterHeadersStatus {
          Buffer::OwnedImpl data("STR");
          decoder_filters_[0]->callbacks_->addDecodedData(data, true);
          if (decode_headers_stop_all) {
            return FilterHeadersStatus::StopAllIterationAndBuffer;
          } else {
            return FilterHeadersStatus::Continue;
          }
        }));
    EXPECT_CALL(*decoder_filters_[0], decodeComplete());
  }