ListenerImpl::newListenerWithFilterChain(const envoy::config::listener::v3::Listener& config,
                                         bool workers_started, uint64_t hash) {
  
  return absl::WrapUnique(
      new ListenerImpl(*this, config, version_info_, parent_, name_, added_via_api_,
                        workers_started,
                        hash, parent_.server_.options().concurrency()));
}