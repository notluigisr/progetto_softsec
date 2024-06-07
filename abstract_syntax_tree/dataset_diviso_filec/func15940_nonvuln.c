void ConnectionManagerImpl::ActiveStreamDecoderFilter::addDownstreamWatermarkCallbacks(
    DownstreamWatermarkCallbacks& watermark_callbacks) {
  
  
  ASSERT(std::find(parent_.watermark_callbacks_.begin(), parent_.watermark_callbacks_.end(),
                   &watermark_callbacks) == parent_.watermark_callbacks_.end());
  parent_.watermark_callbacks_.emplace(parent_.watermark_callbacks_.end(), &watermark_callbacks);
  for (uint32_t i = 0; i < parent_.high_watermark_count_; ++i) {
    watermark_callbacks.onAboveWriteBufferHighWatermark();
  }
}