bool VideoTrack::SetAlphaMode(uint64_t alpha_mode) {
  if (alpha_mode != kNoAlpha && alpha_mode != kAlpha)
    return false;

  alpha_mode_ = alpha_mode;
  return true;
}