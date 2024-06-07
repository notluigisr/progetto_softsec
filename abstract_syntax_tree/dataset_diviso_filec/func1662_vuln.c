void ConnPoolImplBase::checkForIdleAndCloseIdleConnsIfDraining() {
  if (is_draining_for_deletion_) {
    closeIdleConnectionsForDrainingPool();
  }

  if (isIdleImpl()) {
    ENVOY_LOG(debug, "STR",
              is_draining_for_deletion_);
    for (const Instance::IdleCb& cb : idle_callbacks_) {
      cb();
    }
  }
}