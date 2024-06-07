bool Cluster::Finalize() {
  return !write_last_frame_with_duration_ && Finalize(false, 0);
}