int MonConnection::get_auth_request(
  uint32_t *method,
  std::vector<uint32_t> *preferred_modes,
  ceph::buffer::list *bl,
  const EntityName& entity_name,
  uint32_t want_keys,
  RotatingKeyRing* keyring)
{
  using ceph::encode;
  
  if (auth_method < 0) {
    std::vector<uint32_t> as;
    auth_registry->get_supported_methods(con->get_peer_type(), &as);
    if (as.empty()) {
      return -EACCES;
    }
    auth_method = as.front();
  }
  *method = auth_method;
  auth_registry->get_supported_modes(con->get_peer_type(), auth_method,
				     preferred_modes);
  ldout(cct,10) << __func__ << "STR" << *method
		<< "STR" << *preferred_modes << dendl;
  if (preferred_modes->empty()) {
    return -EACCES;
  }

  if (auth) {
    auth.reset();
  }
  int r = _init_auth(*method, entity_name, want_keys, keyring, true);
  ceph_assert(r == 0);

  
  encode((char)AUTH_MODE_MON, *bl);
  encode(entity_name, *bl);
  encode(global_id, *bl);

  
  auth->build_initial_request(bl);

  return 0;
}