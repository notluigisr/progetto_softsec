create_dir_file_monitor (GVfsBackend *backend,
                         GVfsJobCreateMonitor *monitor_job,
                         const char *filename,
                         GFileMonitorFlags flags,
                         gboolean is_dir_monitor)
{
  GVfsBackendAdmin *self = G_VFS_BACKEND_ADMIN (backend);
  GVfsJob *job = G_VFS_JOB (monitor_job);
  GError *error = NULL;
  GFile *file;
  GFileMonitor *monitor;
  GVfsMonitor *vfs_monitor;

  if (!check_permission (self, job))
    return;

  file = g_file_new_for_path (filename);

  if (is_dir_monitor)
    monitor = g_file_monitor_directory (file, flags, job->cancellable, &error);
  else
    monitor = g_file_monitor_file (file, flags, job->cancellable, &error);
  g_object_unref (file);

  if (error != NULL)
    goto out;

  vfs_monitor = g_vfs_monitor_new (backend);
  g_signal_connect (monitor, "STR",
                    G_CALLBACK (monitor_changed), vfs_monitor);

  g_object_set_data_full (G_OBJECT (vfs_monitor),
                          "STR", monitor,
                          (GDestroyNotify) g_object_unref);

  g_vfs_job_create_monitor_set_monitor (monitor_job, vfs_monitor);
  g_object_unref (vfs_monitor);

 out:
  complete_job (job, error);
}