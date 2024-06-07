CtPtr ProtocolV1::handle_connect_message_write(int r) {
  ldout(cct, 20) << __func__ << "STR" << r << dendl;

  if (r < 0) {
    ldout(cct, 2) << __func__ << "STR"
                  << cpp_strerror(r) << dendl;
    return _fault();
  }

  ldout(cct, 20) << __func__
                 << "STR" << dendl;

  return wait_connect_reply();
}