bool SegmentInfo::Finalize(IMkvWriter* writer) const {
  if (!writer)
    return false;

  if (duration_ > 0.0) {
    if (writer->Seekable()) {
      if (duration_pos_ == -1)
        return false;

      const int64_t pos = writer->Position();

      if (writer->Position(duration_pos_))
        return false;

      if (!WriteEbmlElement(writer, libwebm::kMkvDuration,
                            static_cast<float>(duration_)))
        return false;

      if (writer->Position(pos))
        return false;
    }
  }

  return true;
}