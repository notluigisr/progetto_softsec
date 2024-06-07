static win_credential_t *win_credential(pn_ssl_mode_t m)
{
  static const pn_cid_t CID_win_credential = CID_pn_void;
  static const pn_class_t clazz = PN_CLASS(win_credential);
  win_credential_t *c = (win_credential_t *) pn_class_new(&clazz, sizeof(win_credential_t));
  c->mode = m;
  csguard g(&c->cslock);
  pn_incref(c);  
  return c;
}