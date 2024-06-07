CtPtr ProtocolV2::post_client_banner_exchange() {
  ldout(cct, 20) << __func__ << dendl;

  state = AUTH_CONNECTING;

  return send_auth_request();
}