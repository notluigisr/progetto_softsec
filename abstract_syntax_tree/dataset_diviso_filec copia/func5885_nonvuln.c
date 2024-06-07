TEST_F(GrpcHealthCheckerImplTest, SuccessStartFailedFailFirst) {
  setupHC();
  cluster_->prioritySet().getMockHostSet(0)->hosts_ = {
      makeTestHost(cluster_->info_, "STR", simTime())};
  cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagSet(
      Host::HealthFlag::FAILED_ACTIVE_HC);
  cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagSet(
      Host::HealthFlag::PENDING_ACTIVE_HC);

  expectSessionCreate();
  expectHealthcheckStart(0);
  health_checker_->start();

  
  expectHealthcheckStop(0);
  
  
  EXPECT_CALL(*this, onHostStatus(_, HealthTransition::Changed));
  EXPECT_CALL(event_logger_, logUnhealthy(_, _, _, true));
  respondServiceStatus(0, grpc::health::v1::HealthCheckResponse::NOT_SERVING);
  expectHostHealthy(false);
  EXPECT_FALSE(cluster_->prioritySet().getMockHostSet(0)->hosts_[0]->healthFlagGet(
      Host::HealthFlag::PENDING_ACTIVE_HC));

  
  
  expectHealthcheckStart(0);
  test_sessions_[0]->interval_timer_->invokeCallback();

  expectHealthcheckStop(0);
  
  EXPECT_CALL(*this, onHostStatus(_, HealthTransition::ChangePending));
  respondServiceStatus(0, grpc::health::v1::HealthCheckResponse::SERVING);
  expectHostHealthy(false);

  
  expectHealthcheckStart(0);
  test_sessions_[0]->interval_timer_->invokeCallback();

  expectHealthcheckStop(0);
  EXPECT_CALL(*this, onHostStatus(_, HealthTransition::Changed));
  EXPECT_CALL(event_logger_, logAddHealthy(_, _, false));
  respondServiceStatus(0, grpc::health::v1::HealthCheckResponse::SERVING);
  expectHostHealthy(true);
}