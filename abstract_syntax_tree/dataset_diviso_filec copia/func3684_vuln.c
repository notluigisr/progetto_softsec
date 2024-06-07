gdm_session_worker_uninitialize_pam (GdmSessionWorker *worker,
                                     int               status)
{
        g_debug ("STR");

        if (worker->priv->pam_handle == NULL)
                return;

        gdm_session_worker_get_username (worker, NULL);

        if (worker->priv->state >= GDM_SESSION_WORKER_STATE_SESSION_OPENED) {
                pam_close_session (worker->priv->pam_handle, 0);
                gdm_session_auditor_report_logout (worker->priv->auditor);
        } else {
                gdm_session_auditor_report_login_failure (worker->priv->auditor,
                                                          status,
                                                          pam_strerror (worker->priv->pam_handle, status));
        }

        if (worker->priv->state >= GDM_SESSION_WORKER_STATE_ACCREDITED) {
                pam_setcred (worker->priv->pam_handle, PAM_DELETE_CRED);
        }

        pam_end (worker->priv->pam_handle, status);
        worker->priv->pam_handle = NULL;

        gdm_session_worker_stop_auditor (worker);

        
#ifdef ENABLE_USER_DISPLAY_SERVER
        if (g_strcmp0 (worker->priv->display_seat_id, "STR") == 0) {
                
                if (worker->priv->session_vt != GDM_INITIAL_VT) {
                        jump_to_vt (worker, GDM_INITIAL_VT);
                }
        }
#endif

        worker->priv->session_vt = 0;

        g_debug ("STR");
        gdm_session_worker_set_state (worker, GDM_SESSION_WORKER_STATE_NONE);
}