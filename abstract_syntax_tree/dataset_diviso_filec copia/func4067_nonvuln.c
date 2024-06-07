  void reply_message(const Message *m, Payload& pl) {
    pl.who = Payload::PONG;
    bufferlist bl;
    ::encode(pl, bl);
    MPing *rm = new MPing();
    rm->set_data(bl);
    m->get_connection()->send_message(rm);
    lderr(g_ceph_context) << __func__ << "STR" << pl.seq << dendl;
  }