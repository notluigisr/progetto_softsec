g_file_enumerate_children (GFile                *file,
                           const char           *attributes,
                           GFileQueryInfoFlags   flags,
                           GCancellable         *cancellable,
                           GError              **error)
{
  GFileIface *iface;

  g_return_val_if_fail (G_IS_FILE (file), NULL);

  if (g_cancellable_set_error_if_cancelled (cancellable, error))
    return NULL;

  iface = G_FILE_GET_IFACE (file);

  if (iface->enumerate_children == NULL)
    {
      g_set_error_literal (error, G_IO_ERROR,
                           G_IO_ERROR_NOT_SUPPORTED,
                           _("STR"));
      return NULL;
    }

  return (* iface->enumerate_children) (file, attributes, flags,
                                        cancellable, error);
}