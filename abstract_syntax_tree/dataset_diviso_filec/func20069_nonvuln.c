void Downstream::set_request_start_time(
    std::chrono::high_resolution_clock::time_point time) {
  request_start_time_ = std::move(time);
}