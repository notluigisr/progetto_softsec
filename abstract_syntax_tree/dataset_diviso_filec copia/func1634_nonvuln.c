  void expectSessionCreate() {
    
    TestSessionPtr new_test_session(new TestSession());
    new_test_session->timeout_timer_ = new Event::MockTimer(&dispatcher_);
    new_test_session->interval_timer_ = new Event::MockTimer(&dispatcher_);
    test_sessions_.emplace_back(std::move(new_test_session));
    expectClientCreate(test_sessions_.size() - 1);
  }