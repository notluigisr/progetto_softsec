  void TearDown() override {
    HttpIntegrationTest::cleanupUpstreamAndDownstream();
    dispatcher_->clearDeferredDeleteList();
    if (fake_handshaker_server_ != nullptr) {
      fake_handshaker_server_->Shutdown();
    }
    fake_handshaker_server_thread_->join();
  }