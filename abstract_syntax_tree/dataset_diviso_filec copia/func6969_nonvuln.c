flatpak_dir_get_repo_config (FlatpakDir *self)
{
  if (!flatpak_dir_ensure_repo (self, NULL, NULL))
    return NULL;

  return ostree_repo_get_config (self->repo);
}