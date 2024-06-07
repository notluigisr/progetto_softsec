TEST_P(Http2CodecImplTest, PriorityFlood) {
  priorityFlood();
  EXPECT_THROW(client_->sendPendingFrames(), FrameFloodException);
}