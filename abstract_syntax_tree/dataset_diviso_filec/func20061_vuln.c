bool ConnectionImpl::addOutboundFrameFragment(Buffer::OwnedImpl& output, const uint8_t* data,
                                              size_t length) {
  
  
  bool is_outbound_flood_monitored_control_frame = false;
  std::swap(is_outbound_flood_monitored_control_frame, is_outbound_flood_monitored_control_frame_);
  try {
    incrementOutboundFrameCount(is_outbound_flood_monitored_control_frame);
  } catch (const FrameFloodException&) {
    return false;
  }

  auto fragment = Buffer::OwnedBufferFragmentImpl::create(
      absl::string_view(reinterpret_cast<const char*>(data), length),
      is_outbound_flood_monitored_control_frame ? control_frame_buffer_releasor_
                                                : frame_buffer_releasor_);

  
  
  output.addBufferFragment(*fragment.release());
  return true;
}