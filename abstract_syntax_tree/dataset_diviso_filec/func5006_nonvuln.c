flatpak_deploy_get_metadata (FlatpakDeploy *deploy)
{
  return g_key_file_ref (deploy->metadata);
}