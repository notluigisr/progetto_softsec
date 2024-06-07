TEST_P(ConnectionLimitIntegrationTest, TestListenerLimit) {
  std::function<void()> init_func = [this]() {
    setListenerLimit(2);
    initialize();
  };

  doTest(init_func, "STR");
}