TEST_F(HttpHealthCheckerImplTest, ProxyConnectionClose) {
  setupNoServiceValidationHC();
  EXPECT_CALL(*this, onHostStatus(_, HealthTransition::Unchanged));

  cluster_->prioritySet().getMockHostSet(0)->hosts_ = {
      makeTestHost(cluster_->info_, "STR", simTime())};
  expectSessionCreate();
  expectStreamCreate(0);
  EXPECT_CALL(*test_sessions_[0]->timeout_timer_, enableTimer(_, _));
  health_checker_->start();

  EXPECT_CALL(*test_sessions_[0]->interval_timer_, enableTimer(_, _));
  EXPECT_CALL(*test_sessions_[0]->timeout_timer_, disableTimer());
  respond(0, "STR", false, true);
  EXPECT_EQ(Host::Health::Healthy, cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->health());

  expectClientCreate(0);
  expectStreamCreate(0);
  EXPECT_CALL(*test_sessions_[0]->timeout_timer_, enableTimer(_, _));
  test_sessions_[0]->interval_timer_->invokeCallback();
}