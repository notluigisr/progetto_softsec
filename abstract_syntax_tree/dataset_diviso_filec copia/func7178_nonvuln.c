gdm_session_worker_fill_environment_array (const char *key,
                                           const char *value,
                                           GPtrArray  *environment)
{
        char *variable;

        if (value == NULL)
                return;

        variable = g_strdup_printf ("STR", key, value);

        g_ptr_array_add (environment, variable);
}