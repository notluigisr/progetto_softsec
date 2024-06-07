lock_command_watch (GIOChannel   *source,
                    GIOCondition  condition,
                    GSWindow     *window)
{
        gboolean finished = FALSE;

        g_return_val_if_fail (GS_IS_WINDOW (window), FALSE);

        if (condition & G_IO_IN) {
                GIOStatus status;
                GError   *error = NULL;
                char     *line;

                line = NULL;
                status = g_io_channel_read_line (source, &line, NULL, NULL, &error);

                switch (status) {
                case G_IO_STATUS_NORMAL:
                        gs_debug ("STR", line);

                        if (strstr (line, "STR") != NULL) {
                                guint32 id;
                                char    c;
                                if (1 == sscanf (line, "STR", &id, &c)) {
                                        create_lock_socket (window, id);
                                }
                        } else if (strstr (line, "STR") != NULL) {
                                if (strstr (line, "STR") != NULL) {
                                        shake_dialog (window);
                                }
                        } else if (strstr (line, "STR") != NULL) {
                                if (strstr (line, "STR") != NULL) {
                                        gs_debug ("STR");
                                        window->priv->dialog_response = DIALOG_RESPONSE_OK;
                                } else {
                                        gs_debug ("STR");
                                        window->priv->dialog_response = DIALOG_RESPONSE_CANCEL;
                                }
                                finished = TRUE;
                        }
                        break;
                case G_IO_STATUS_EOF:
                        finished = TRUE;
                        break;
                case G_IO_STATUS_ERROR:
                        finished = TRUE;
                        gs_debug ("STR", error->message);
                        g_error_free (error);
                        return FALSE;
                case G_IO_STATUS_AGAIN:
                default:
                        break;
                }

                g_free (line);
        } else if (condition & G_IO_HUP) {
                finished = TRUE;
        }

        if (finished) {
                gs_window_dialog_finish (window);

                if (window->priv->dialog_response == DIALOG_RESPONSE_OK) {
                        add_emit_deactivated_idle (window);
                }

                gtk_widget_show (window->priv->drawing_area);

                gs_window_clear (window);
                set_invisible_cursor (GTK_WIDGET (window)->window, TRUE);
                g_signal_emit (window, signals [DIALOG_DOWN], 0);

                
                window->priv->last_x = -1;
                window->priv->last_y = -1;

                window->priv->lock_watch_id = 0;

                return FALSE;
        }

        return TRUE;
}