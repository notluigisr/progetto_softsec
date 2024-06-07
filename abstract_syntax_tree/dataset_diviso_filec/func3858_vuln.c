bool AuthNoneAuthorizeHandler::verify_authorizer(CephContext *cct, KeyStore *keys,
						 bufferlist& authorizer_data, bufferlist& authorizer_reply,
						 EntityName& entity_name, uint64_t& global_id, AuthCapsInfo& caps_info, CryptoKey& session_key,
uint64_t *auid)
{
  bufferlist::iterator iter = authorizer_data.begin();

  try {
    __u8 struct_v = 1;
    ::decode(struct_v, iter);
    ::decode(entity_name, iter);
    ::decode(global_id, iter);
  } catch (const buffer::error &err) {
    ldout(cct, 0) << "STR" << dendl;
    return false;
  }

  caps_info.allow_all = true;

  return true;
}