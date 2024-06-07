CtPtr ProtocolV2::handle_auth_request_more(ceph::bufferlist &payload)
{
  ldout(cct, 20) << __func__
		 << "STR" << payload.length() << dendl;

  if (state != AUTH_ACCEPTING_MORE) {
    lderr(cct) << __func__ << "STR" << dendl;
    return _fault();
  }

  auto auth_more = AuthRequestMoreFrame::Decode(payload);
  return _handle_auth_request(auth_more.auth_payload(), true);
}