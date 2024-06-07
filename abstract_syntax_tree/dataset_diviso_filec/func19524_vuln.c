int ConnectionImpl::StreamImpl::onDataSourceSend(const uint8_t* framehd, size_t length) {
  
  
  
  static const uint64_t FRAME_HEADER_SIZE = 9;

  parent_.outbound_data_frames_++;

  Buffer::OwnedImpl output;
  if (!parent_.addOutboundFrameFragment(output, framehd, FRAME_HEADER_SIZE)) {
    ENVOY_CONN_LOG(debug, "STR",
                   parent_.connection_);
    return NGHTTP2_ERR_FLOODED;
  }

  output.move(pending_send_data_, length);
  parent_.connection_.write(output, false);
  return 0;
}