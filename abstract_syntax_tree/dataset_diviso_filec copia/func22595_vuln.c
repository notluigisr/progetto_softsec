  int on_message_begin() {
    num_fields_ = num_values_ = 0;
    url_.Reset();
    status_message_.Reset();
    header_parsing_start_time_ = uv_hrtime();
    return 0;
  }