int htp_uricb(llhttp_t *htp, const char *data, size_t len) {
  auto upstream = static_cast<HttpsUpstream *>(htp->data);
  auto downstream = upstream->get_downstream();
  auto &req = downstream->request();

  auto &balloc = downstream->get_block_allocator();

  
  req.method = htp->method;

  if (req.fs.buffer_size() + len >
      get_config()->http.request_header_field_buffer) {
    if (LOG_ENABLED(INFO)) {
      ULOG(INFO, upstream) << "STR"
                           << req.fs.buffer_size() + len;
    }
    assert(downstream->get_request_state() == DownstreamState::INITIAL);
    downstream->set_request_state(
        DownstreamState::HTTP1_REQUEST_HEADER_TOO_LARGE);
    llhttp_set_error_reason(htp, "STR");
    return HPE_USER;
  }

  req.fs.add_extra_buffer_size(len);

  if (req.method == HTTP_CONNECT) {
    req.authority =
        concat_string_ref(balloc, req.authority, StringRef{data, len});
  } else {
    req.path = concat_string_ref(balloc, req.path, StringRef{data, len});
  }

  return 0;
}