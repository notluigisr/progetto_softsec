ssize_t ProtocolV2::write_message(Message *m, bool more) {
  FUNCTRACE(cct);
  ceph_assert(connection->center->in_thread());
  m->set_seq(++out_seq);

  connection->lock.lock();
  uint64_t ack_seq = in_seq;
  ack_left = 0;
  connection->lock.unlock();

  ceph_msg_header &header = m->get_header();
  ceph_msg_footer &footer = m->get_footer();

  ceph_msg_header2 header2{header.seq,        header.tid,
                           header.type,       header.priority,
                           header.version,
                           init_le32(0),      header.data_off,
                           init_le64(ack_seq),
                           footer.flags,      header.compat_version,
                           header.reserved};

  auto message = MessageFrame::Encode(
			     header2,
			     m->get_payload(),
			     m->get_middle(),
			     m->get_data());
  connection->outgoing_bl.append(message.get_buffer(session_stream_handlers));

  ldout(cct, 5) << __func__ << "STR" << m
                << "STR" << *m << dendl;

  m->trace.event("STR");
  ldout(cct, 20) << __func__ << "STR" << m->get_seq()
                 << "STR" << entity_name_t(messenger->get_myname())
                 << "STR" << header2.data_off
                 << dendl;
  ssize_t total_send_size = connection->outgoing_bl.length();
  ssize_t rc = connection->_try_send(more);
  if (rc < 0) {
    ldout(cct, 1) << __func__ << "STR"
                  << cpp_strerror(rc) << dendl;
  } else {
    connection->logger->inc(
        l_msgr_send_bytes, total_send_size - connection->outgoing_bl.length());
    ldout(cct, 10) << __func__ << "STR" << m
                   << (rc ? "STR") << dendl;
  }
  if (m->get_type() == CEPH_MSG_OSD_OP)
    OID_EVENT_TRACE_WITH_MSG(m, "STR", false);
  else if (m->get_type() == CEPH_MSG_OSD_OPREPLY)
    OID_EVENT_TRACE_WITH_MSG(m, "STR", false);
  m->put();

  return rc;
}