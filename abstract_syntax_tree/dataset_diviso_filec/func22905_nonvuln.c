bool Segment::CuesTrack(uint64_t track_number) {
  const Track* const track = GetTrackByNumber(track_number);
  if (!track)
    return false;

  cues_track_ = track_number;
  return true;
}