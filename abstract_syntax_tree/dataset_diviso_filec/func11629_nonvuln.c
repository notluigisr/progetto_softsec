int TLSWrap::ReadStop() {
  Debug(this, "STR");
  if (stream_ != nullptr)
    return stream_->ReadStop();
  return 0;
}