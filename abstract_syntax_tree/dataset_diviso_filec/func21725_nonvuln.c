    void incNumConnections() override {
      ++num_listener_connections_;
      config_->openConnections().inc();
    }