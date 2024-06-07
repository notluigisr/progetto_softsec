void HTTPSession::onConnectionSendWindowClosed() {
  if(!txnEgressQueue_.empty()) {
    VLOG(4) << *this << "STR";
    if (sessionStats_) {
      sessionStats_->recordSessionStalled();
    }
  }
  DCHECK(!flowControlTimeout_.isScheduled());
  if (infoCallback_) {
    infoCallback_->onFlowControlWindowClosed(*this);
  }
  auto timeout = flowControlTimeout_.getTimeoutDuration();
  if (timeout != std::chrono::milliseconds(0)) {
    timeout_.scheduleTimeout(&flowControlTimeout_, timeout);
  } else {
    timeout_.scheduleTimeout(&flowControlTimeout_);
  }
}