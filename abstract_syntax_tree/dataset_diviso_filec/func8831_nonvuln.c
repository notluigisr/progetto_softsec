RequestEncoder& ClientConnectionImpl::newStream(ResponseDecoder& response_decoder) {
  
  
  ASSERT(connection_.readEnabled());

  ASSERT(!pending_response_.has_value());
  ASSERT(pending_response_done_);
  pending_response_.emplace(*this, std::move(bytes_meter_before_stream_), &response_decoder);
  pending_response_done_ = false;
  return pending_response_.value().encoder_;
}