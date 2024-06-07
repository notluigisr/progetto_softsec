uint64 WriteFrame(IMkvWriter* writer, const Frame* const frame,
                  Cluster* cluster) {
  if (!writer || !frame || !frame->IsValid() || !cluster ||
      !cluster->timecode_scale())
    return 0;

  
  
  
  
  const int64 relative_timecode = cluster->GetRelativeTimecode(
      frame->timestamp() / cluster->timecode_scale());
  if (relative_timecode < 0 || relative_timecode > kMaxBlockTimecode)
    return 0;

  return frame->CanBeSimpleBlock() ?
             WriteSimpleBlock(writer, frame, relative_timecode) :
             WriteBlock(writer, frame, relative_timecode,
                        cluster->timecode_scale());
}