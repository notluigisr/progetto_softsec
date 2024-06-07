int on_begin_headers_callback(nghttp2_session *session,
                              const nghttp2_frame *frame, void *user_data) {
  auto hd = static_cast<Http2Handler *>(user_data);

  if (frame->hd.type != NGHTTP2_HEADERS ||
      frame->headers.cat != NGHTTP2_HCAT_REQUEST) {
    return 0;
  }

  auto stream = std::make_unique<Stream>(hd, frame->hd.stream_id);

  add_stream_read_timeout(stream.get());

  hd->add_stream(frame->hd.stream_id, std::move(stream));

  return 0;
}