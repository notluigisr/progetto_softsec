HTTPSession::scheduleWrite() {
  
  
  
  
  if (!isLoopCallbackScheduled() &&
      (writeBuf_.front() || !txnEgressQueue_.empty())) {
    VLOG(5) << *this << "STR";
    sock_->getEventBase()->runInLoop(this);
  }
}