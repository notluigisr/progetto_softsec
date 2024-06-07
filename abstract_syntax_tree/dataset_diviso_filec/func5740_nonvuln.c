Http2Session::~Http2Session() {
  CHECK_EQ(flags_ & SESSION_STATE_HAS_SCOPE, 0);
  if (!object().IsEmpty())
    ClearWrap(object());
  persistent().Reset();
  CHECK(persistent().IsEmpty());
  Unconsume();
  DEBUG_HTTP2SESSION(this, "STR");
  nghttp2_session_del(session_);
}