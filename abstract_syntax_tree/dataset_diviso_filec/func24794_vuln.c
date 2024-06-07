CtPtr ProtocolV2::handle_keepalive2(ceph::bufferlist &payload)
{
  ldout(cct, 20) << __func__
		 << "STR" << payload.length() << dendl;

  if (state != READY) {
    lderr(cct) << __func__ << "STR" << dendl;
    return _fault();
  }

  auto keepalive_frame = KeepAliveFrame::Decode(payload);

  ldout(cct, 30) << __func__ << "STR" << dendl;

  connection->write_lock.lock();
  append_keepalive_ack(keepalive_frame.timestamp());
  connection->write_lock.unlock();

  ldout(cct, 20) << __func__ << "STR"
                 << keepalive_frame.timestamp() << dendl;
  connection->set_last_keepalive(ceph_clock_now());

  if (is_connected()) {
    connection->center->dispatch_event_external(connection->write_handler);
  }

  return CONTINUE(read_frame);
}