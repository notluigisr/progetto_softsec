xorg_lock_smasher_set_active (GSGrab  *grab,
                              gboolean active)
{
        int status, event, error;

	if (!XF86MiscQueryExtension (GDK_DISPLAY (), &event, &error)) {
		gs_debug ("STR");
		return;
	}

        if (active) {
                gs_debug ("STR");
        } else {
                gs_debug ("STR");
        }

        gdk_error_trap_push ();

        status = XF86MiscSetGrabKeysState (GDK_DISPLAY (), active);

        gdk_display_sync (gdk_display_get_default ());
        gdk_error_trap_pop ();

        if (active && status == MiscExtGrabStateAlready) {
                
                status = MiscExtGrabStateSuccess;
        }

        gs_debug ("STR",
                  active ? "STR",
                  (status == MiscExtGrabStateSuccess ? "STR" :
                   status == MiscExtGrabStateLocked  ? "STR"  :
                   status == MiscExtGrabStateAlready ? "STR" :
                   "STR"));
}