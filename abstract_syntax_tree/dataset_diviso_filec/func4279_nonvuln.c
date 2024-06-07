Network::FilterStatus Context::onData(Buffer::Instance& data, bool end_stream) {
  network_downstream_data_buffer_ = &data;
  auto result = onDownstreamData(data.length(), end_stream);
  network_downstream_data_buffer_ = nullptr;
  return result;
}