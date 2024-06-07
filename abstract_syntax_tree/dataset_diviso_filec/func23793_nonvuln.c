bool ConnectionManagerImpl::ActiveStream::handleDataIfStopAll(ActiveStreamFilterBase& filter,
                                                              Buffer::Instance& data,
                                                              bool& filter_streaming) {
  if (filter.stoppedAll()) {
    ASSERT(!filter.canIterate());
    filter_streaming =
        filter.iteration_state_ == ActiveStreamFilterBase::IterationState::StopAllWatermark;
    filter.commonHandleBufferData(data);
    return true;
  }
  return false;
}