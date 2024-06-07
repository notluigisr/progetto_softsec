auth_check_idle (GSLockPlug *plug)
{
        gboolean     res;
        gboolean     again;
        static guint loop_counter = 0;

        again = TRUE;
        res = do_auth_check (plug);

        if (res) {
                again = FALSE;
                g_idle_add ((GSourceFunc)quit_response_ok, NULL);
        } else {
                loop_counter++;

                if (loop_counter < MAX_FAILURES) {
                        gs_debug ("STR", loop_counter);
                        g_timeout_add (3000, (GSourceFunc)reset_idle_cb, plug);
                } else {
                        gs_debug ("STR");
                        again = FALSE;
                        gtk_main_quit ();
                }
        }

        return again;
}