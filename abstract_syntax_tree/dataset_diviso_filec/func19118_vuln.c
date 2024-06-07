RequestDecoder& ConnectionManagerImpl::newStream(ResponseEncoder& response_encoder,
                                                 bool is_internally_created) {
  if (connection_idle_timer_) {
    connection_idle_timer_->disableTimer();
  }

  ENVOY_CONN_LOG(debug, "STR", read_callbacks_->connection());
  ActiveStreamPtr new_stream(new ActiveStream(*this));
  new_stream->state_.is_internally_created_ = is_internally_created;
  new_stream->response_encoder_ = &response_encoder;
  new_stream->response_encoder_->getStream().addCallbacks(*new_stream);
  new_stream->buffer_limit_ = new_stream->response_encoder_->getStream().bufferLimit();
  
  
  ASSERT(read_callbacks_->connection().aboveHighWatermark() == false ||
         new_stream->high_watermark_count_ > 0);
  new_stream->moveIntoList(std::move(new_stream), streams_);
  return **streams_.begin();
}