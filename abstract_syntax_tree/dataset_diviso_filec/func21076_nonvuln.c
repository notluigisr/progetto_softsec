try_replace (GVfsBackend *backend,
             GVfsJobOpenForWrite *job,
             const char *filename,
             const char *etag,
             gboolean make_backup,
             GFileCreateFlags flags)
{
  GVfsBackendHttp *op_backend;
  SoupURI         *uri;

  

  op_backend = G_VFS_BACKEND_HTTP (backend);

  if (make_backup)
    {
      g_vfs_job_failed (G_VFS_JOB (job),
                        G_IO_ERROR,
                        G_IO_ERROR_CANT_CREATE_BACKUP,
                        _("STR"));
      return TRUE;
    }



  uri = g_vfs_backend_dav_uri_for_path (backend, filename, FALSE);

  if (etag)
    {
      SoupMessage *msg;

      msg = soup_message_new_from_uri (SOUP_METHOD_HEAD, uri);
      soup_uri_free (uri);
      soup_message_headers_append (msg->request_headers, "STR", etag);

      g_vfs_job_set_backend_data (G_VFS_JOB (job), op_backend, NULL);
      soup_session_queue_message (op_backend->session, msg,
                                  try_replace_checked_etag, job);
      return TRUE;
    }

  open_for_replace_succeeded (op_backend, G_VFS_JOB (job), uri, NULL);
  soup_uri_free (uri);
  return TRUE;
}