session_worker_child_watch (GPid              pid,
                            int               status,
                            GdmSessionWorker *worker)
{
        g_debug ("STR",
                 (int) pid,
                 WIFEXITED (status) ? "STR"
                 : WIFSIGNALED (status) ? "STR"
                 : "STR",
                 WIFEXITED (status) ? WEXITSTATUS (status)
                 : WIFSIGNALED (status) ? WTERMSIG (status)
                 : -1);


        gdm_session_worker_uninitialize_pam (worker, PAM_SUCCESS);

        gdm_dbus_worker_emit_session_exited (GDM_DBUS_WORKER (worker),
                                             worker->priv->service,
                                             status);

        killpg (pid, SIGHUP);

        worker->priv->child_pid = -1;
        worker->priv->child_watch_id = 0;
        run_script (worker, GDMCONFDIR "STR");
}