int ConnectionImpl::onFrameSend(const nghttp2_frame* frame) {
  
  
  
  
  ENVOY_CONN_LOG(trace, "STR", connection_, static_cast<uint64_t>(frame->hd.type));
  switch (frame->hd.type) {
  case NGHTTP2_GOAWAY: {
    ENVOY_CONN_LOG(debug, "STR", connection_, frame->goaway.error_code);
    if (frame->goaway.error_code != NGHTTP2_NO_ERROR) {
      return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    break;
  }

  case NGHTTP2_RST_STREAM: {
    ENVOY_CONN_LOG(debug, "STR", connection_, frame->rst_stream.error_code);
    stats_.tx_reset_.inc();
    break;
  }

  case NGHTTP2_HEADERS:
  case NGHTTP2_DATA: {
    StreamImpl* stream = getStream(frame->hd.stream_id);
    stream->local_end_stream_sent_ = frame->hd.flags & NGHTTP2_FLAG_END_STREAM;
    break;
  }
  }

  return 0;
}