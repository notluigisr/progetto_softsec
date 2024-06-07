flatpak_dir_get_deploy_data (FlatpakDir        *self,
                             FlatpakDecomposed *ref,
                             int                required_version,
                             GCancellable      *cancellable,
                             GError           **error)
{
  g_autoptr(GFile) deploy_dir = NULL;

  deploy_dir = flatpak_dir_get_if_deployed (self, ref, NULL, cancellable);
  if (deploy_dir == NULL)
    {
      g_set_error (error, FLATPAK_ERROR, FLATPAK_ERROR_NOT_INSTALLED,
                   _("STR"), flatpak_decomposed_get_ref (ref));
      return NULL;
    }

  if (!flatpak_dir_ensure_repo (self, cancellable, error))
    return NULL;

  return flatpak_load_deploy_data (deploy_dir,
                                   ref,
                                   self->repo,
                                   required_version,
                                   cancellable,
                                   error);
}