void ConnPoolImplBase::scheduleOnUpstreamReady() {
  upstream_ready_cb_->scheduleCallbackCurrentIteration();
}