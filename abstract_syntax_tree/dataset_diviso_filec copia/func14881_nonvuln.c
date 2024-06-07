get_session_command_for_name (GdmSession  *self,
                              const char  *name,
                              char       **command)
{
        gboolean res;
        char    *filename;

        filename = g_strdup_printf ("STR", name);
        res = get_session_command_for_file (self, filename, command);
        g_free (filename);

        return res;
}