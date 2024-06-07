void ConnectionManagerImpl::ActiveStream::chargeStats(const ResponseHeaderMap& headers) {
  uint64_t response_code = Utility::getResponseStatus(headers);
  filter_manager_.streamInfo().response_code_ = response_code;

  if (filter_manager_.streamInfo().health_check_request_) {
    return;
  }

  Upstream::HostDescriptionConstSharedPtr upstream_host =
      connection_manager_.read_callbacks_->upstreamHost();

  if (upstream_host != nullptr) {
    Upstream::ClusterRequestResponseSizeStatsOptRef req_resp_stats =
        upstream_host->cluster().requestResponseSizeStats();
    if (req_resp_stats.has_value()) {
      req_resp_stats->get().upstream_rs_headers_size_.recordValue(headers.byteSize());
    }
  }

  
  const absl::optional<std::string>& response_code_details =
      filter_manager_.streamInfo().responseCodeDetails();
  if (response_code_details.has_value() &&
      response_code_details == Envoy::StreamInfo::ResponseCodeDetails::get().InternalRedirect) {
    return;
  }

  connection_manager_.stats_.named_.downstream_rq_completed_.inc();
  connection_manager_.listener_stats_.downstream_rq_completed_.inc();
  if (CodeUtility::is1xx(response_code)) {
    connection_manager_.stats_.named_.downstream_rq_1xx_.inc();
    connection_manager_.listener_stats_.downstream_rq_1xx_.inc();
  } else if (CodeUtility::is2xx(response_code)) {
    connection_manager_.stats_.named_.downstream_rq_2xx_.inc();
    connection_manager_.listener_stats_.downstream_rq_2xx_.inc();
  } else if (CodeUtility::is3xx(response_code)) {
    connection_manager_.stats_.named_.downstream_rq_3xx_.inc();
    connection_manager_.listener_stats_.downstream_rq_3xx_.inc();
  } else if (CodeUtility::is4xx(response_code)) {
    connection_manager_.stats_.named_.downstream_rq_4xx_.inc();
    connection_manager_.listener_stats_.downstream_rq_4xx_.inc();
  } else if (CodeUtility::is5xx(response_code)) {
    connection_manager_.stats_.named_.downstream_rq_5xx_.inc();
    connection_manager_.listener_stats_.downstream_rq_5xx_.inc();
  }
}