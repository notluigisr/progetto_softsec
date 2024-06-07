void Downstream::add_rcbuf(nghttp2_rcbuf *rcbuf) {
  nghttp2_rcbuf_incref(rcbuf);
  rcbufs_.push_back(rcbuf);
}