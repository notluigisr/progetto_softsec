on_handle_get_password (GoaPasswordBased      *interface,
                        GDBusMethodInvocation *invocation,
                        const gchar           *id,
                        gpointer               user_data)
{
  GoaObject *object;
  GoaAccount *account;
  GoaProvider *provider;
  GError *error;
  GVariant *credentials;
  gchar *password;

  

  password = NULL;
  credentials = NULL;

  object = GOA_OBJECT (g_dbus_interface_get_object (G_DBUS_INTERFACE (interface)));
  account = goa_object_peek_account (object);
  provider = goa_provider_get_for_provider_type (goa_account_get_provider_type (account));

  error = NULL;
  credentials = goa_utils_lookup_credentials_sync (provider,
                                                   object,
                                                   NULL, 
                                                   &error);
  if (credentials == NULL)
    {
      g_dbus_method_invocation_take_error (invocation, error);
      goto out;
    }

  if (!g_variant_lookup (credentials, "STR", &password))
    {
      g_dbus_method_invocation_return_error (invocation,
                                             GOA_ERROR,
                                             GOA_ERROR_FAILED, 
                                             _("STR"),
                                             id);
      goto out;
    }

  goa_password_based_complete_get_password (interface, invocation, password);

 out:
  g_free (password);
  if (credentials != NULL)
    g_variant_unref (credentials);
  g_object_unref (provider);
  return TRUE; 
}