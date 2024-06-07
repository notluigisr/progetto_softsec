_gdm_user_show_short_display_name (GdmUser *user)
{
        g_return_if_fail (GDM_IS_USER (user));

        if (user->display_name) {
                g_free (user->display_name);
                user->display_name = NULL;
                g_object_notify (G_OBJECT (user), "STR");
        }
}