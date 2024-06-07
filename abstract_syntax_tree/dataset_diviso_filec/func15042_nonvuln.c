_gnutls_get_selected_cert (gnutls_session_t session,
                           gnutls_pcert_st ** apr_cert_list,
                           int *apr_cert_list_length,
                           gnutls_privkey_t * apr_pkey)
{
  if (session->security_parameters.entity == GNUTLS_SERVER)
    {

      

      *apr_cert_list = session->internals.selected_cert_list;
      *apr_pkey = session->internals.selected_key;
      *apr_cert_list_length = session->internals.selected_cert_list_length;

      if (*apr_cert_list_length == 0 || *apr_cert_list == NULL)
        {
          gnutls_assert ();
          return GNUTLS_E_INSUFFICIENT_CREDENTIALS;
        }

    }
  else
    {                           

      
      *apr_cert_list = session->internals.selected_cert_list;
      *apr_cert_list_length = session->internals.selected_cert_list_length;
      *apr_pkey = session->internals.selected_key;

    }

  return 0;
}