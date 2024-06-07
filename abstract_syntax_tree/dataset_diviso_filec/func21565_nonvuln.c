void ConnectionManagerImpl::handleCodecException(const char* error) {
  ENVOY_CONN_LOG(debug, "STR", read_callbacks_->connection(), error);

  
  
  resetAllStreams();

  
  
  read_callbacks_->connection().close(Network::ConnectionCloseType::FlushWriteAndDelay);
}