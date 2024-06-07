bool Cluster::DoWriteFrame(const Frame* const frame) {
  if (!frame || !frame->IsValid())
    return false;

  if (!PreWriteBlock())
    return false;

  const uint64_t element_size = WriteFrame(writer_, frame, this);
  if (element_size == 0)
    return false;

  PostWriteBlock(element_size);
  last_block_timestamp_[frame->track_number()] = frame->timestamp();
  return true;
}