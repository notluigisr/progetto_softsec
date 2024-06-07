void Downstream::disable_upstream_wtimer() {
  if (get_config()->http2.timeout.stream_write == 0.) {
    return;
  }
  auto loop = upstream_->get_client_handler()->get_loop();
  disable_timer(loop, &upstream_wtimer_);
}