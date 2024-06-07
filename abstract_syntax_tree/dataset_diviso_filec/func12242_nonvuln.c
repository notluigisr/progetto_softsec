void ConnectionImpl::releaseOutboundControlFrame() {
  ASSERT(outbound_control_frames_ >= 1);
  --outbound_control_frames_;
  releaseOutboundFrame();
}