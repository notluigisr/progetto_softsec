bool Segment::DoNewClusterProcessing(uint64_t track_number,
                                     uint64_t frame_timestamp_ns, bool is_key) {
  for (;;) {
    
    
    const int result = TestFrame(track_number, frame_timestamp_ns, is_key);
    if (result < 0)  
      return false;

    
    force_new_cluster_ = false;

    
    if (result > 0 && !MakeNewCluster(frame_timestamp_ns))
      return false;

    
    const int frame_count = WriteFramesAll();
    if (frame_count < 0)  
      return false;

    
    
    if (result <= 1)
      return true;

    
    
    
  }
}