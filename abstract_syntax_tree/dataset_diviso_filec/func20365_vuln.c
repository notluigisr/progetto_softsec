on_screen_monitors_changed (GdkScreen *screen,
                            GSManager *manager)
{
        gs_debug ("STR",
                  gdk_screen_get_number (screen),
                  gdk_screen_get_n_monitors (screen));
}