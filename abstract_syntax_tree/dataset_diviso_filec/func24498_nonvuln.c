goa_utils_check_duplicate (GoaClient              *client,
                           const gchar            *identity,
                           const gchar            *provider_type,
                           GoaPeekInterfaceFunc    func,
                           GError                **error)
{
  GList *accounts;
  GList *l;
  gboolean ret;

  ret = FALSE;

  accounts = goa_client_get_accounts (client);
  for (l = accounts; l != NULL; l = l->next)
    {
      GoaObject *object = GOA_OBJECT (l->data);
      GoaAccount *account;
      gpointer *interface;
      const gchar *identity_from_object;
      const gchar *provider_type_from_object;

      account = goa_object_peek_account (object);
      interface = (*func) (object);
      if (interface == NULL)
        continue;

      provider_type_from_object = goa_account_get_provider_type (account);
      if (g_strcmp0 (provider_type_from_object, provider_type) != 0)
        continue;

      identity_from_object = goa_account_get_identity (account);
      if (g_strcmp0 (identity_from_object, identity) == 0)
        {
          const gchar *presentation_identity;
          const gchar *provider_name;

          presentation_identity = goa_account_get_presentation_identity (account);
          provider_name = goa_account_get_provider_name (account);
          g_set_error (error,
                       GOA_ERROR,
                       GOA_ERROR_ACCOUNT_EXISTS,
                       _("STR"),
                       provider_name,
                       presentation_identity);
          goto out;
        }
    }

  ret = TRUE;

 out:
  g_list_free_full (accounts, g_object_unref);
  return ret;
}