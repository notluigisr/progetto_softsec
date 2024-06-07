SegmentInfo::SegmentInfo()
    : duration_(-1.0),
      muxing_app_(NULL),
      timecode_scale_(1000000ULL),
      writing_app_(NULL),
      date_utc_(LLONG_MIN),
      duration_pos_(-1) {}