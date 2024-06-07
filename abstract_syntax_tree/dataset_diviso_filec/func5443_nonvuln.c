void Http2Session::OnStreamAllocImpl(size_t suggested_size,
                                     uv_buf_t* buf,
                                     void* ctx) {
  Http2Session* session = static_cast<Http2Session*>(ctx);
  buf->base = session->stream_alloc();
  buf->len = kAllocBufferSize;
}