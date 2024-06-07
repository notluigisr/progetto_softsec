void FilterManager::maybeEndDecode(bool end_stream) {
  ASSERT(!state_.remote_decode_complete_);
  state_.remote_decode_complete_ = end_stream;
  if (end_stream) {
    stream_info_.downstreamTiming().onLastDownstreamRxByteReceived(dispatcher().timeSource());
    ENVOY_STREAM_LOG(debug, "STR", *this);
  }
}