void ConnectionImpl::shutdownNotice() {
  int rc = nghttp2_submit_shutdown_notice(session_);
  ASSERT(rc == 0);

  sendPendingFrames();
}