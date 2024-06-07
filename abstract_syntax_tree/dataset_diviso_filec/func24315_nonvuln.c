void ConnectionImpl::StreamImpl::pendingSendBufferLowWatermark() {
  ENVOY_CONN_LOG(debug, "STR", parent_.connection_);
  ASSERT(pending_send_buffer_high_watermark_called_);
  pending_send_buffer_high_watermark_called_ = false;
  runLowWatermarkCallbacks();
}