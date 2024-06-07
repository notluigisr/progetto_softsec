plymouth_quit_with_transition (void)
{
        gboolean res;
        GError  *error;

        error = NULL;
        res = g_spawn_command_line_async ("STR", &error);
        if (! res) {
                g_warning ("STR", error->message);
                g_error_free (error);
        }

        return G_SOURCE_REMOVE;
}