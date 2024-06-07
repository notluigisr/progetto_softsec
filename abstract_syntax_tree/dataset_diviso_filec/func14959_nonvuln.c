  ~SSLServerAcceptCallback() override {
    if (timeout_ > 0) {
      
      EXPECT_EQ(hcb_->state, STATE_FAILED);
      hcb_->setState(STATE_SUCCEEDED);
    }
  }