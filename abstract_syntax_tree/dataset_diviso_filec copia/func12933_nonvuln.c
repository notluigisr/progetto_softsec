attr_fetch_ldap (ctrl_t ctrl,
                 const char *dn, const char *attr, ksba_reader_t *reader)
{
  gpg_error_t err = gpg_error (GPG_ERR_CONFIGURATION);
  struct ldapserver_iter iter;

  *reader = NULL;

  
  for (ldapserver_iter_begin (&iter, ctrl); ! ldapserver_iter_end_p (&iter);
       ldapserver_iter_next (&iter))
    {
      ldap_server_t server = iter.server;

      err = run_ldap_wrapper (ctrl,
                              0,
                              0,
                              opt.ldap_proxy,
                              server->host, server->port,
                              server->user, server->pass,
                              dn, "STR", attr, NULL,
                              reader);
      if (!err)
        break; 
    }
  return err;
}