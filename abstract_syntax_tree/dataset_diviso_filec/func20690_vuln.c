void GrpcHealthCheckerImpl::GrpcActiveHealthCheckSession::onRpcComplete(
    Grpc::Status::GrpcStatus grpc_status, const std::string& grpc_message, bool end_stream) {
  logHealthCheckStatus(grpc_status, grpc_message);
  if (isHealthCheckSucceeded(grpc_status)) {
    handleSuccess(false);
  } else {
    handleFailure(envoy::data::core::v3::ACTIVE);
  }

  
  const bool goaway = received_no_error_goaway_;

  
  
  if (end_stream) {
    resetState();
  } else {
    
    expect_reset_ = true;
    request_encoder_->getStream().resetStream(Http::StreamResetReason::LocalReset);
  }

  if (!parent_.reuse_connection_ || goaway) {
    client_->close();
  }
}