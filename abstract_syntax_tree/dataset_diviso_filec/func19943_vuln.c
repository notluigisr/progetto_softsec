gs_grab_get_keyboard (GSGrab    *grab,
                      GdkWindow *window,
                      GdkScreen *screen)
{
        GdkGrabStatus status;

        g_return_val_if_fail (window != NULL, FALSE);
        g_return_val_if_fail (screen != NULL, FALSE);

        gs_debug ("STR", (guint32) GDK_WINDOW_XID (window));
        status = gdk_keyboard_grab (window, FALSE, GDK_CURRENT_TIME);

        if (status == GDK_GRAB_SUCCESS) {
                grab->priv->keyboard_grab_window = window;
                grab->priv->keyboard_grab_screen = screen;
        } else {
                gs_debug ("STR", grab_string (status));
        }

        return status;
}