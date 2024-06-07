void ConnectionManagerImpl::ActiveStreamFilterBase::clearRouteCache() {
  parent_.cached_route_ = absl::optional<Router::RouteConstSharedPtr>();
  parent_.cached_cluster_info_ = absl::optional<Upstream::ClusterInfoConstSharedPtr>();
}