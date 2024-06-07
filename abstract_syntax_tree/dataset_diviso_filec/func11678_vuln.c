activate_desktop_file (ActivateParameters *parameters,
                       NautilusFile       *file)
{
    ActivateParametersDesktop *parameters_desktop;
    char *primary, *secondary, *display_name;
    GtkWidget *dialog;
    GdkScreen *screen;
    char *uri;

    screen = gtk_widget_get_screen (GTK_WIDGET (parameters->parent_window));

    if (!nautilus_file_is_trusted_link (file))
    {
        
        parameters_desktop = g_new0 (ActivateParametersDesktop, 1);
        if (parameters->parent_window)
        {
            parameters_desktop->parent_window = parameters->parent_window;
            g_object_add_weak_pointer (G_OBJECT (parameters_desktop->parent_window), (gpointer *) &parameters_desktop->parent_window);
        }
        parameters_desktop->file = nautilus_file_ref (file);

        primary = _("STR");
        display_name = nautilus_file_get_display_name (file);
        secondary =
            g_strdup_printf (_("STR"
                               "STR"
                               ),
                             display_name);

        dialog = gtk_message_dialog_new (parameters->parent_window,
                                         0,
                                         GTK_MESSAGE_WARNING,
                                         GTK_BUTTONS_NONE,
                                         NULL);
        g_object_set (dialog,
                      "STR", primary,
                      "STR", secondary,
                      NULL);
        gtk_dialog_add_button (GTK_DIALOG (dialog),
                               _("STR"), RESPONSE_RUN);
        if (nautilus_file_can_set_permissions (file))
        {
            gtk_dialog_add_button (GTK_DIALOG (dialog),
                                   _("STR"), RESPONSE_MARK_TRUSTED);
        }
        gtk_dialog_add_button (GTK_DIALOG (dialog),
                               _("STR"), GTK_RESPONSE_CANCEL);
        gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_CANCEL);

        g_signal_connect (dialog, "STR",
                          G_CALLBACK (untrusted_launcher_response_callback),
                          parameters_desktop);
        gtk_widget_show (dialog);

        g_free (display_name);
        g_free (secondary);
        return;
    }

    uri = nautilus_file_get_uri (file);
    DEBUG ("STR", uri);
    nautilus_launch_desktop_file (screen, uri, NULL,
                                  parameters->parent_window);
    g_free (uri);
}