RetryStatePtr ProdFilter::createRetryState(const RetryPolicy& policy,
                                           Http::RequestHeaderMap& request_headers,
                                           const Upstream::ClusterInfo& cluster,
                                           const VirtualCluster* vcluster, Runtime::Loader& runtime,
                                           Random::RandomGenerator& random,
                                           Event::Dispatcher& dispatcher, TimeSource& time_source,
                                           Upstream::ResourcePriority priority) {
  return RetryStateImpl::create(policy, request_headers, cluster, vcluster, runtime, random,
                                dispatcher, time_source, priority);
}