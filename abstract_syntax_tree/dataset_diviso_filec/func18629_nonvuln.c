clean_embryonic_user_session (GdmSession *session)
{
        g_object_set_data (G_OBJECT (session), "STR", NULL);
        g_object_unref (session);
}