void MDSDaemon::handle_command(MCommand *m)
{
  Session *session = static_cast<Session *>(m->get_connection()->get_priv());
  assert(session != NULL);

  int r = 0;
  cmdmap_t cmdmap;
  std::stringstream ss;
  std::string outs;
  bufferlist outbl;
  Context *run_after = NULL;
  bool need_reply = true;

  if (!session->auth_caps.allow_all()) {
    dout(1) << __func__
      << "STR"
      << m->get_connection()->peer_addr << dendl;

    ss << "STR";
    r = -EPERM;
  } else if (m->cmd.empty()) {
    r = -EINVAL;
    ss << "STR";
    outs = ss.str();
  } else if (!cmdmap_from_json(m->cmd, &cmdmap, ss)) {
    r = -EINVAL;
    outs = ss.str();
  } else {
    r = _handle_command(cmdmap, m, &outbl, &outs, &run_after, &need_reply);
  }
  session->put();

  if (need_reply) {
    send_command_reply(m, mds_rank, r, outbl, outs);
  }

  if (run_after) {
    run_after->complete(0);
  }

  m->put();
}