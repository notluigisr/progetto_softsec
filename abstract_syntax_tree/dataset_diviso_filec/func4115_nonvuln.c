void InstanceImpl::startWorkers() {
  listener_manager_->startWorkers(*guard_dog_);
  initialization_timer_->complete();
  
  updateServerStats();
  workers_started_ = true;
  
  
  restarter_.drainParentListeners();
  drain_manager_->startParentShutdownSequence();
}