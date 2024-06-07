TEST_F(TcpHealthCheckerImplTest, PassiveFailure) {
  InSequence s;

  setupNoData();
  cluster_->prioritySet().getMockHostSet(0)->hosts_ = {
      makeTestHost(cluster_->info_, "STR", simTime())};
  expectSessionCreate();
  expectClientCreate();
  EXPECT_CALL(*connection_, write(_, _)).Times(0);
  EXPECT_CALL(*timeout_timer_, enableTimer(_, _));
  EXPECT_CALL(event_logger_, logEjectUnhealthy(_, _, _));
  EXPECT_CALL(event_logger_, logUnhealthy(_, _, _, true));
  health_checker_->start();

  
  cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthChecker().setUnhealthy(
      HealthCheckHostMonitor::UnhealthyType::ImmediateHealthCheckFail);
  cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthChecker().setUnhealthy(
      HealthCheckHostMonitor::UnhealthyType::ImmediateHealthCheckFail);
  EXPECT_TRUE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::FAILED_ACTIVE_HC));
  EXPECT_TRUE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::EXCLUDED_VIA_IMMEDIATE_HC_FAIL));
  EXPECT_EQ(Host::Health::Unhealthy,
            cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->health());

  
  EXPECT_CALL(*connection_, close(_));
  EXPECT_CALL(*timeout_timer_, disableTimer());
  EXPECT_CALL(*interval_timer_, enableTimer(_, _));
  connection_->raiseEvent(Network::ConnectionEvent::Connected);
  EXPECT_TRUE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::FAILED_ACTIVE_HC));
  EXPECT_TRUE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::EXCLUDED_VIA_IMMEDIATE_HC_FAIL));
  EXPECT_EQ(Host::Health::Unhealthy,
            cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->health());

  
  expectClientCreate();
  EXPECT_CALL(*timeout_timer_, enableTimer(_, _));
  interval_timer_->invokeCallback();

  EXPECT_CALL(*connection_, close(_));
  EXPECT_CALL(event_logger_, logAddHealthy(_, _, false));
  EXPECT_CALL(*timeout_timer_, disableTimer());
  EXPECT_CALL(*interval_timer_, enableTimer(_, _));
  connection_->raiseEvent(Network::ConnectionEvent::Connected);
  EXPECT_FALSE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::FAILED_ACTIVE_HC));
  EXPECT_FALSE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::EXCLUDED_VIA_IMMEDIATE_HC_FAIL));
  EXPECT_EQ(Host::Health::Healthy, cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->health());

  EXPECT_EQ(2UL, cluster_->info_->stats_store_.counter("STR").value());
  EXPECT_EQ(2UL, cluster_->info_->stats_store_.counter("STR").value());
  EXPECT_EQ(2UL, cluster_->info_->stats_store_.counter("STR").value());
  EXPECT_EQ(2UL, cluster_->info_->stats_store_.counter("STR").value());
}