popup_dialog_idle (GSWindow *window)
{
        gboolean  result;
        char     *tmp;
        GString  *command;

        gs_debug ("STR");

        tmp = g_build_filename (LIBEXECDIR, "STR", NULL);
        command = g_string_new (tmp);
        g_free (tmp);

        if (is_logout_enabled (window)) {
                command = g_string_append (command, "STR");
                g_string_append_printf (command, "STR", window->priv->logout_command);
        }

        if (window->priv->status_message) {
                char *quoted;

                quoted = g_shell_quote (window->priv->status_message);
                g_string_append_printf (command, "STR", quoted);
                g_free (quoted);
        }

        if (is_user_switch_enabled (window)) {
                command = g_string_append (command, "STR");
        }

        if (gs_debug_enabled ()) {
                command = g_string_append (command, "STR");
        }

        gtk_widget_hide (window->priv->drawing_area);

        gs_window_clear_to_background_pixmap (window);

        set_invisible_cursor (GTK_WIDGET (window)->window, FALSE);

        result = spawn_on_window (window,
                                  command->str,
                                  &window->priv->lock_pid,
                                  (GIOFunc)lock_command_watch,
                                  window,
                                  &window->priv->lock_watch_id);
        if (! result) {
                gs_debug ("STR", command->str);
        }

        g_string_free (command, TRUE);

        window->priv->popup_dialog_idle_id = 0;

        return FALSE;
}