void upstream_timeoutcb(struct ev_loop *loop, ev_timer *w, int revents) {
  auto downstream = static_cast<Downstream *>(w->data);
  auto upstream = downstream->get_upstream();

  auto which = revents == EV_READ ? "STR";

  if (LOG_ENABLED(INFO)) {
    DLOG(INFO, downstream) << "STR"
                           << downstream->get_stream_id() << "STR" << which;
  }

  downstream->disable_upstream_rtimer();
  downstream->disable_upstream_wtimer();

  upstream->on_timeout(downstream);
}