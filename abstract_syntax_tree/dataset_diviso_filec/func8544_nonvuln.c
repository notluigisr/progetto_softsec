TEST_F(HttpHealthCheckerImplTest, ServicePatternDoesNotMatchFail) {
  setupServiceRegexPatternValidationHC();
  EXPECT_CALL(event_logger_, logUnhealthy(_, _, _, true));
  EXPECT_CALL(runtime_.snapshot_, featureEnabled("STR", 100))
      .WillOnce(Return(true));

  EXPECT_CALL(*this, onHostStatus(_, HealthTransition::Changed));
  EXPECT_CALL(event_logger_, logEjectUnhealthy(_, _, _));

  cluster_->prioritySet().getMockHostSet(0)->hosts_ = {
      makeTestHost(cluster_->info_, "STR", simTime())};
  cluster_->info_->stats().upstream_cx_total_.inc();
  expectSessionCreate();
  expectStreamCreate(0);
  EXPECT_CALL(*test_sessions_[0]->timeout_timer_, enableTimer(_, _));
  health_checker_->start();

  EXPECT_CALL(runtime_.snapshot_, getInteger("STR", _));
  EXPECT_CALL(runtime_.snapshot_, getInteger("STR", _))
      .WillOnce(Return(45000));
  EXPECT_CALL(*test_sessions_[0]->interval_timer_,
              enableTimer(std::chrono::milliseconds(45000), _));
  EXPECT_CALL(*test_sessions_[0]->timeout_timer_, disableTimer());
  absl::optional<std::string> health_checked_cluster("STR");
  respond(0, "STR", false, false, true, false, health_checked_cluster);
  EXPECT_TRUE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::FAILED_ACTIVE_HC));
  EXPECT_EQ(Host::Health::Unhealthy,
            cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->health());
}