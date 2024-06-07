void ProtocolV2::stop() {
  ldout(cct, 1) << __func__ << dendl;
  if (state == CLOSED) {
    return;
  }

  if (connection->delay_state) connection->delay_state->flush();

  std::lock_guard<std::mutex> l(connection->write_lock);

  reset_recv_state();
  discard_out_queue();

  connection->_stop();

  can_write = false;
  state = CLOSED;
}