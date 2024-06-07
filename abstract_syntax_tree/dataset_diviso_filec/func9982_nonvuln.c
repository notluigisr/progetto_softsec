flatpak_remote_state_new (void)
{
  FlatpakRemoteState *state = g_new0 (FlatpakRemoteState, 1);

  state->refcount = 1;
  state->sideload_repos = g_ptr_array_new_with_free_func ((GDestroyNotify)flatpak_sideload_state_free);
  state->subsummaries = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, (GDestroyNotify)variant_maybe_unref);
  return state;
}