TEST_F(ConnectionHandlerTest, ListenerFilterReportError) {
  InSequence s;

  TestListener* test_listener = addListener(1, true, false, "STR");
  Network::MockListener* listener = new Network::MockListener();
  Network::ListenerCallbacks* listener_callbacks;
  EXPECT_CALL(dispatcher_, createListener_(_, _, _))
      .WillOnce(
          Invoke([&](Network::Socket&, Network::ListenerCallbacks& cb, bool) -> Network::Listener* {
            listener_callbacks = &cb;
            return listener;
          }));
  EXPECT_CALL(test_listener->socket_, localAddress());
  handler_->addListener(*test_listener);

  Network::MockListenerFilter* first_filter = new Network::MockListenerFilter();
  Network::MockListenerFilter* last_filter = new Network::MockListenerFilter();

  EXPECT_CALL(factory_, createListenerFilterChain(_))
      .WillRepeatedly(Invoke([&](Network::ListenerFilterManager& manager) -> bool {
        manager.addAcceptFilter(Network::ListenerFilterPtr{first_filter});
        manager.addAcceptFilter(Network::ListenerFilterPtr{last_filter});
        return true;
      }));
  
  EXPECT_CALL(*first_filter, onAccept(_))
      .WillOnce(Invoke([&](Network::ListenerFilterCallbacks& cb) -> Network::FilterStatus {
        cb.socket().close();
        return Network::FilterStatus::StopIteration;
      }));
  
  EXPECT_CALL(*last_filter, onAccept(_)).Times(0);
  Network::MockConnectionSocket* accepted_socket = new NiceMock<Network::MockConnectionSocket>();
  listener_callbacks->onAccept(Network::ConnectionSocketPtr{accepted_socket});

  dispatcher_.clearDeferredDeleteList();
  
  EXPECT_CALL(dispatcher_, createTimer_(_)).Times(0);
  
  EXPECT_CALL(manager_, findFilterChain(_)).Times(0);

  EXPECT_CALL(*listener, onDestroy());
}