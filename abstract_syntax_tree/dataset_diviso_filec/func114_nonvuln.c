bool Segment::WriteFramesLessThan(uint64_t timestamp) {
  
  
  
  if (frames_size_ > 0 && cluster_list_size_ > 0) {
    if (!frames_)
      return false;

    Cluster* const cluster = cluster_list_[cluster_list_size_ - 1];
    if (!cluster)
      return false;

    int32_t shift_left = 0;

    
    
    for (int32_t i = 1; i < frames_size_; ++i) {
      const Frame* const frame_curr = frames_[i];

      if (frame_curr->timestamp() > timestamp)
        break;

      const Frame* const frame_prev = frames_[i - 1];
      if (frame_prev->discard_padding() != 0)
        doc_type_version_ = 4;
      if (!cluster->AddFrame(frame_prev))
        return false;

      if (new_cuepoint_ && cues_track_ == frame_prev->track_number()) {
        if (!AddCuePoint(frame_prev->timestamp(), cues_track_))
          return false;
      }

      ++shift_left;
      if (frame_prev->timestamp() > last_timestamp_) {
        last_timestamp_ = frame_prev->timestamp();
        last_track_timestamp_[frame_prev->track_number() - 1] =
            frame_prev->timestamp();
      }

      delete frame_prev;
    }

    if (shift_left > 0) {
      if (shift_left >= frames_size_)
        return false;

      const int32_t new_frames_size = frames_size_ - shift_left;
      for (int32_t i = 0; i < new_frames_size; ++i) {
        frames_[i] = frames_[i + shift_left];
      }

      frames_size_ = new_frames_size;
    }
  }

  return true;
}