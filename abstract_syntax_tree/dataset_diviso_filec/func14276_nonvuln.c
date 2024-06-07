  void setUpstreamBytesMeter(const BytesMeterSharedPtr& upstream_bytes_meter) override {
    
    upstream_bytes_meter->addWireBytesSent(upstream_bytes_meter_->wireBytesSent());
    upstream_bytes_meter->addWireBytesReceived(upstream_bytes_meter_->wireBytesReceived());
    upstream_bytes_meter->addHeaderBytesSent(upstream_bytes_meter_->headerBytesSent());
    upstream_bytes_meter->addHeaderBytesReceived(upstream_bytes_meter_->headerBytesReceived());
    upstream_bytes_meter_ = upstream_bytes_meter;
  }