void HttpHealthCheckerImpl::HttpActiveHealthCheckSession::onTimeout() {
  request_in_flight_ = false;
  if (client_) {
    ENVOY_CONN_LOG(debug, "STR", *client_,
                   HostUtility::healthFlagsToString(*host_));

    
    expect_reset_ = true;

    client_->close();
  }
}