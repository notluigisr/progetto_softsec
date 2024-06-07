TEST_P(MessengerTest, SyntheticInjectTest2) {
  g_ceph_context->_conf->set_val("STR");
  g_ceph_context->_conf->set_val("STR");
  SyntheticWorkload test_msg(8, 16, GetParam(), 100,
                             Messenger::Policy::lossless_peer_reuse(0),
                             Messenger::Policy::lossless_peer_reuse(0));
  for (int i = 0; i < 100; ++i) {
    if (!(i % 10)) lderr(g_ceph_context) << "STR" << i << dendl;
    test_msg.generate_connection();
  }
  gen_type rng(time(NULL));
  for (int i = 0; i < 1000; ++i) {
    if (!(i % 10)) {
      lderr(g_ceph_context) << "STR" << dendl;
      test_msg.print_internal_state();
    }
    boost::uniform_int<> true_false(0, 99);
    int val = true_false(rng);
    if (val > 90) {
      test_msg.generate_connection();
    } else if (val > 80) {
      test_msg.drop_connection();
    } else if (val > 10) {
      test_msg.send_message();
    } else {
      usleep(rand() % 500 + 100);
    }
  }
  test_msg.wait_for_done();
  g_ceph_context->_conf->set_val("STR");
  g_ceph_context->_conf->set_val("STR");
}