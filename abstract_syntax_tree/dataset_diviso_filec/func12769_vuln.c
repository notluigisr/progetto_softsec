int ConnectionImpl::saveHeader(const nghttp2_frame* frame, HeaderString&& name,
                               HeaderString&& value) {
  StreamImpl* stream = getStream(frame->hd.stream_id);
  if (!stream) {
    
    
    
    
    
    
    stats_.headers_cb_no_stream_.inc();
    return 0;
  }

  stream->saveHeader(std::move(name), std::move(value));
  if (stream->headers_->byteSize() > max_request_headers_kb_ * 1024) {
    
    stats_.header_overflow_.inc();
    return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
  } else {
    return 0;
  }
}