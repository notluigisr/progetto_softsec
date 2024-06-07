PendingStream::~PendingStream() {
  parent_.host()->cluster().stats().upstream_rq_pending_active_.dec();
  parent_.host()->cluster().resourceManager(parent_.priority()).pendingRequests().dec();
}