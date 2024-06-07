void GrpcHealthCheckerImpl::GrpcActiveHealthCheckSession::onGoAway(
    Http::GoAwayErrorCode error_code) {
  ENVOY_CONN_LOG(debug, "STR", *client_,
                 HostUtility::healthFlagsToString(*host_));
  
  
  
  
  if (request_encoder_ && error_code == Http::GoAwayErrorCode::NoError) {
    received_no_error_goaway_ = true;
    return;
  }

  
  if (request_encoder_) {
    handleFailure(envoy::data::core::v3::NETWORK);
    expect_reset_ = true;
    request_encoder_->getStream().resetStream(Http::StreamResetReason::LocalReset);
  }
  client_->close();
}