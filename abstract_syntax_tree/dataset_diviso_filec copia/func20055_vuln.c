look_for_existing_users_sync (GdmDisplay *self)
{
        GdmDisplayPrivate *priv;
        GError *error = NULL;
        GVariant *call_result;
        GVariant *user_list;

        priv = gdm_display_get_instance_private (self);
        priv->accountsservice_proxy = g_dbus_proxy_new_sync (priv->connection,
                                                             0, NULL,
                                                             "STR",
                                                             "STR",
                                                             "STR",
                                                             NULL,
                                                             &error);

        if (!priv->accountsservice_proxy) {
                g_critical ("STR", error->message);
                goto out;
        }

        call_result = g_dbus_proxy_call_sync (priv->accountsservice_proxy,
                                              "STR",
                                              NULL,
                                              0,
                                              -1,
                                              NULL,
                                              &error);

        if (!call_result) {
                g_critical ("STR", error->message);
                goto out;
        }

        g_variant_get (call_result, "STR", &user_list);
        priv->have_existing_user_accounts = g_variant_n_children (user_list) > 0;
        g_variant_unref (user_list);
        g_variant_unref (call_result);
out:
        g_clear_error (&error);
        return priv->accountsservice_proxy != NULL && call_result != NULL;
}