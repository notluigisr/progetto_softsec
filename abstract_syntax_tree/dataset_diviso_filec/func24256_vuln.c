int Http2Stream::DoWrite(WriteWrap* req_wrap,
                         uv_buf_t* bufs,
                         size_t nbufs,
                         uv_stream_t* send_handle) {
  CHECK_NULL(send_handle);
  Http2Scope h2scope(this);
  if (!IsWritable() || IsDestroyed()) {
    req_wrap->Done(UV_EOF);
    return 0;
  }
  Debug(this, "STR", id_, nbufs);
  for (size_t i = 0; i < nbufs; ++i) {
    
    
    queue_.emplace(nghttp2_stream_write {
      i == nbufs - 1 ? req_wrap : nullptr,
      bufs[i]
    });
    IncrementAvailableOutboundLength(bufs[i].len);
  }
  CHECK_NE(nghttp2_session_resume_data(**session_, id_), NGHTTP2_ERR_NOMEM);
  return 0;
}