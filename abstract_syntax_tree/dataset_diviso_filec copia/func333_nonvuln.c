gdm_session_worker_get_environment_variable (GdmSessionWorker *worker,
                                             const char       *key)
{
        return g_strdup (pam_getenv (worker->priv->pam_handle, key));
}