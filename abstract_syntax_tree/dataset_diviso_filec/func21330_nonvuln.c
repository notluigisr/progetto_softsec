listener_check_activation (GSListener *listener)
{
        gboolean inhibited;
        gboolean res;

        gs_debug ("STR");

        if (! listener->priv->activation_enabled) {
                return TRUE;
        }

        if (! listener->priv->session_idle) {
                return TRUE;
        }

        
        inhibited = listener_ref_entry_is_present (listener, REF_ENTRY_TYPE_INHIBIT);

        res = FALSE;
        if (! inhibited) {
                gs_debug ("STR");
                res = gs_listener_set_active (listener, TRUE);
        }

        return res;
}