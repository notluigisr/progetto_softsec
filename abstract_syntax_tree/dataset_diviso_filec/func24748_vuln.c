int ConnectionImpl::onStreamClose(int32_t stream_id, uint32_t error_code) {
  StreamImpl* stream = getStream(stream_id);
  if (stream) {
    ENVOY_CONN_LOG(debug, "STR", connection_, error_code);
    if (!stream->remote_end_stream_ || !stream->local_end_stream_) {
      StreamResetReason reason;
      if (stream->reset_due_to_messaging_error_) {
        
        
        
        
        
        
        
        reason = StreamResetReason::LocalReset;
      } else {
        reason = error_code == NGHTTP2_REFUSED_STREAM ? StreamResetReason::RemoteRefusedStreamReset
                                                      : StreamResetReason::RemoteReset;
      }

      stream->runResetCallbacks(reason);
    }

    connection_.dispatcher().deferredDelete(stream->removeFromList(active_streams_));
    
    
    
    nghttp2_session_consume(session_, stream_id, stream->unconsumed_bytes_);
    stream->unconsumed_bytes_ = 0;
    nghttp2_session_set_stream_user_data(session_, stream->stream_id_, nullptr);
  }

  return 0;
}