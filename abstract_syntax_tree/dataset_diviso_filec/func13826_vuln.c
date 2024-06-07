gdm_session_worker_uninitialize_pam (GdmSessionWorker *worker,
                                     int               status)
{
        g_debug ("STR");

        if (worker->priv->pam_handle == NULL)
                return;

        if (worker->priv->state >= GDM_SESSION_WORKER_STATE_SESSION_OPENED) {
                pam_close_session (worker->priv->pam_handle, 0);
                gdm_session_auditor_report_logout (worker->priv->auditor);

#ifdef  HAVE_LOGINDEVPERM
                
                if (worker->priv->display_device != NULL &&
                   (strncmp (worker->priv->display_device, "STR")) == 0 ||
                    strcmp  (worker->priv->display_device, "STR") == 0)) {
                        g_debug ("STR",
                                 worker->priv->username,
                                 worker->priv->display_device);
                        (void) di_devperm_logout (worker->priv->display_device);
                }
#endif  

        } else {
                void *p;

                if ((pam_get_item (worker->priv->pam_handle, PAM_USER, &p)) == PAM_SUCCESS) {
                        gdm_session_auditor_set_username (worker->priv->auditor, (const char *)p);
                }

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

        g_debug ("STR");
        worker->priv->state = GDM_SESSION_WORKER_STATE_NONE;
}