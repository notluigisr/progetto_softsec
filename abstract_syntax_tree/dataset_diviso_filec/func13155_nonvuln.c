void InstanceImpl::failHealthcheck(bool fail) {
  live_.store(!fail);
  server_stats_->live_.set(live_.load());
}