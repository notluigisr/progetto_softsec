TEST_P(Http2CodecImplTest, PingFloodCounterReset) {
  static const int kMaxOutboundControlFrames = 100;
  max_outbound_control_frames_ = kMaxOutboundControlFrames;
  initialize();

  TestRequestHeaderMapImpl request_headers;
  HttpTestUtility::addDefaultHeaders(request_headers);
  EXPECT_CALL(request_decoder_, decodeHeaders_(_, false));
  request_encoder_->encodeHeaders(request_headers, false);

  for (int i = 0; i < kMaxOutboundControlFrames; ++i) {
    EXPECT_EQ(0, nghttp2_submit_ping(client_->session(), NGHTTP2_FLAG_NONE, nullptr));
  }

  int ack_count = 0;
  Buffer::OwnedImpl buffer;
  ON_CALL(server_connection_, write(_, _))
      .WillByDefault(Invoke([&buffer, &ack_count](Buffer::Instance& frame, bool) {
        ++ack_count;
        buffer.move(frame);
      }));

  
  EXPECT_NO_THROW(client_->sendPendingFrames());
  EXPECT_EQ(ack_count, kMaxOutboundControlFrames);

  
  buffer.drain(buffer.length() / 2);

  
  for (int i = 0; i < kMaxOutboundControlFrames / 2; ++i) {
    EXPECT_EQ(0, nghttp2_submit_ping(client_->session(), NGHTTP2_FLAG_NONE, nullptr));
  }
  
  
  EXPECT_NO_THROW(client_->sendPendingFrames());

  
  EXPECT_EQ(0, nghttp2_submit_ping(client_->session(), NGHTTP2_FLAG_NONE, nullptr));
  EXPECT_THROW(client_->sendPendingFrames(), ServerCodecError);
}