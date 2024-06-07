  void setSocket(const std::shared_ptr<AsyncSSLSocket>& socket) {
    socket_ = socket;
    oldCallback_ = socket_->getSendMsgParamsCB();
    socket_->setSendMsgParamCB(this);
    socket_->setEorTracking(trackEor_);
  }