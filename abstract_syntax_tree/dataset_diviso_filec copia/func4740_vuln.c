dane_verification_status_print (unsigned int status,
                       gnutls_datum_t * out, unsigned int flags)
{
  gnutls_buffer_st str;
  int ret;

  _gnutls_buffer_init (&str);

  if (status == 0)
    _gnutls_buffer_append_str (&str, _("STR"));
  else
    _gnutls_buffer_append_str (&str, _("STR"));

  if (status & DANE_VERIFY_CA_CONSTRAINTS_VIOLATED)
    _gnutls_buffer_append_str (&str, _("STR"));

  if (status & DANE_VERIFY_CERT_DIFFERS)
    _gnutls_buffer_append_str (&str, _("STR"));

  if (status & DANE_VERIFY_NO_DANE_INFO)
    _gnutls_buffer_append_str (&str, _("STR"));

  ret = _gnutls_buffer_to_datum( &str, out);
  if (out->size > 0) out->size--;
      
  return ret;
}