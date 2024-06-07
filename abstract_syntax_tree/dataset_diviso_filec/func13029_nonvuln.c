flatpak_dir_remove_ref (FlatpakDir        *self,
                        const char        *remote_name,
                        const char        *ref, 
                        GCancellable      *cancellable,
                        GError           **error)
{
  if (flatpak_dir_use_system_helper (self, NULL))
    {
      const char *installation = flatpak_dir_get_id (self);

      if (!flatpak_dir_system_helper_call_remove_local_ref (self,
                                                            FLATPAK_HELPER_REMOVE_LOCAL_REF_FLAGS_NONE,
                                                            remote_name,
                                                            ref,
                                                            installation ? installation : "",
                                                            cancellable,
                                                            error))
        return FALSE;

      return TRUE;
    }

  if (!ostree_repo_set_ref_immediate (self->repo,
                                      remote_name,
                                      ref,
                                      NULL,
                                      cancellable,
                                      error))
    return FALSE;

  return TRUE;
}